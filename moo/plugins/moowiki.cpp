/*
 *   moowiki.cpp
 *
 *   In-editor Wiki preview pane.  Renders Habitat / UseMod-style wiki
 *   syntax to HTML and feeds it through MooHtml — the same widget used
 *   by the Markdown preview.  The wiki-to-HTML converter is implemented
 *   in-tree so there's no external library to find; everything compiles
 *   into medit itself.
 *
 *   ─────────── Wiki syntax: attribution ───────────────────────────────
 *
 *   The syntax and rendering rules implemented below are a clean-room C
 *   reimplementation of a pragmatic subset of the wiki dialect used by
 *   Habitat, taken from its Perl renderer module:
 *
 *       Habitat / habitat/lib/Habitat/Render.pm
 *       https://github.com/fangq/habitat
 *
 *   Habitat is Copyright (C) 2009, 2010, 2014  Qianqian Fang
 *       <fangq (at) nmr.mgh.harvard.edu>   (GPL v2)
 *
 *   Habitat itself descends from UseModWiki 1.0 (Sep 2003) by
 *       Clifford A. Adams <caadams@usemod.com>   and
 *       Sunir Shah        <sunir@sunir.org>     (GPL),
 *   which was derived from AtisWiki 0.3 (Markus Denker, 1998), which
 *   was based on Peter Merel's CVWiki patches and Ward Cunningham's
 *   original WikiWikiWeb.  All upstream copyrights are preserved by
 *   reference; this file ships under medit's LGPL terms.
 *
 *   ─────────── Supported syntax (subset of Habitat) ───────────────────
 *
 *     Inline:
 *       '''bold'''                  <strong>
 *       ''italic''                  <em>
 *       `code`                      <code>
 *       <b>/<i>/<strong>/<em>/<tt>  passthrough
 *       <br>                        <br>
 *       [[Page]]                    <a href="Page">Page</a>
 *       [[Page|text]]               <a href="Page">text</a>
 *       [[Page#anchor]]             <a href="Page#anchor">Page#anchor</a>
 *       [url text]                  <a href="url">text</a>
 *       [url]                       <a href="url">[N]</a>
 *       http://...                  autolink
 *       WikiWord                    <a href="WikiWord">WikiWord</a>
 *       \  (end of line)            line continuation
 *
 *     Block:
 *       = H1 =  ... ====== H6 ======
 *       * item / ** sub                       unordered list
 *       # item / ## sub                       ordered list
 *       ; term : def                          definition list
 *       : indented text                       indented (dl/dd)
 *       (leading space/tab)                   preformatted
 *       ----                                  horizontal rule
 *       ||cell||cell||                        table row
 *       !!cell!!cell!!                        table header row
 *       <nowiki>...</nowiki>                  literal, no markup
 *       <pre>...</pre> / <code>...</code>     preformatted (multi-line)
 *
 *   Many of Habitat's deeper features (templates, transclusion,
 *   inter-site Site:Page links, RFC/ISBN autolinks, named anchors,
 *   raw <html> blocks, page-local regex rules, the TOC and tree
 *   generators, etc.) are intentionally NOT implemented here — they
 *   either need the live %Pages/filesystem layer or are easier to
 *   skip for a preview pane.  Unrecognised wiki constructs fall
 *   through as their HTML-escaped text rather than being mangled.
 *
 *   When MOO_BUILD_WIKI is not defined the whole file compiles to a
 *   no-op _moo_wiki_plugin_init() so plugin-builtin.cpp can call it
 *   unconditionally.
 *
 *   Copyright (C) 2026 — part of medit.
 *
 *   This file is part of medit.  medit is free software; you can
 *   redistribute it and/or modify it under the terms of the
 *   GNU Lesser General Public License as published by the
 *   Free Software Foundation; either version 2.1 of the License,
 *   or (at your option) any later version.
 */

#include "config.h"
#include "mooedit/mooplugin.h"
#include "mooedit/mooplugin-macro.h"
#include "mooedit/mooeditwindow.h"
#include "mooedit/mooedit.h"
#include "mooutils/moostock.h"
#include "mooutils/mooi18n.h"
#include "mooutils/mooprefs.h"

#define WIKI_PLUGIN_ID "WikiPreview"
#define WIKI_SHOW_PREF "Plugins/WikiPreview/show"

#ifdef MOO_BUILD_WIKI

#include <gtk/gtk.h>
#include <string.h>
#include "mooapp/moohtml.h"
#include "mooedit/mooeditview.h"

typedef struct {
    MooPlugin parent;
} WikiPlugin;

typedef struct {
    MooWinPlugin parent;
    MooPane     *pane;
    GtkWidget   *html_view;

    gulong         notify_active_doc_id;
    GtkTextBuffer *current_buffer;
    gulong         buffer_changed_id;
    guint          render_timeout_id;
} WikiWindowPlugin;

#define WIKI_DEBOUNCE_MS 200

/* ════════════════════════════════════════════════════════════════════════
 * Wiki → HTML converter
 *
 * Two-pass design:
 *   1. Protected-region pass: pull <nowiki>...</nowiki>, <pre>...</pre>
 *      and <code>...</code> blocks out of the source and replace them
 *      with FS-style placeholders (\x01<N>\x01).  Their original
 *      content is stashed in `saved` and re-inserted after the rest of
 *      the pipeline has run.
 *   2. Line-oriented block pass: iterate lines, manage a block stack
 *      (ul/ol/dl/pre/table/p), apply CommonMarkup inline rules to text
 *      content.
 *
 * Conservative on purpose: anything that doesn't match a known rule is
 * left as-is (HTML-escaped earlier), so unknown wiki syntax degrades to
 * plain text rather than mangled output.
 * ════════════════════════════════════════════════════════════════════════
 */

/* TOC entry: one per "== # Heading ==" we see, plus level for indent. */
typedef struct {
    int   level;     /* 1..6, matches <hN> */
    char *title;     /* g_strdup'd display text (no leading "# ") */
    char *anchor;    /* g_strdup'd slug for href="#..." */
} WikiTocEntry;

typedef struct {
    GString    *out;          /* accumulating HTML */
    GPtrArray  *saved;        /* g_free-ownership of protected-region strings */
    GSList     *blocks;       /* stack of strdup'd "ul"/"ol"/"dl"/"pre"/"table" */
    GArray     *block_depth;  /* matching depth per block stack entry */
    gboolean    in_para;
    int         link_counter; /* for numbered [url] refs */

    /* TOC support — populated as headings are emitted, replayed at the
     * end when wiki_to_html post-processes the buffer for <toc> markers. */
    GPtrArray  *toc;          /* of WikiTocEntry*, owned */
    int         anchor_seq;   /* dedupe counter for duplicate heading slugs */

    /* Set of anchor names already emitted so a stray duplicate
     * "[#name]" doesn't trip libxml2's "ID already defined" warning.
     * Both the heading anchor (== # …) and the inline [#name] register
     * here. */
    GHashTable *anchors_seen;
} WikiCtx;

static void
wiki_toc_entry_free (gpointer p)
{
    WikiTocEntry *e = (WikiTocEntry *) p;
    if (!e) return;
    g_free (e->title);
    g_free (e->anchor);
    g_free (e);
}

/* GitHub-ish slug: lowercase, runs of non-alphanum collapse to a single
 * '-', leading/trailing '-' stripped.  Returns NULL if nothing slug-able
 * is left (caller can fall back to "section-N" in that case). */
static char *
wiki_slugify (const char *text)
{
    if (!text) return NULL;
    GString *s = g_string_new (NULL);
    gboolean prev_dash = TRUE;
    for (const char *p = text; *p; p = g_utf8_next_char (p))
    {
        gunichar ch = g_utf8_get_char (p);
        if (g_unichar_isalnum (ch))
        {
            g_string_append_unichar (s, g_unichar_tolower (ch));
            prev_dash = FALSE;
        }
        else if (!prev_dash)
        {
            g_string_append_c (s, '-');
            prev_dash = TRUE;
        }
    }
    while (s->len > 0 && s->str[s->len - 1] == '-')
        g_string_truncate (s, s->len - 1);
    if (s->len == 0) { g_string_free (s, TRUE); return NULL; }
    return g_string_free (s, FALSE);
}

/* Stash a chunk of raw HTML behind a numeric placeholder so the rest
 * of the pipeline can't touch it.  Returns a fresh g_strdup'd string
 * the caller is responsible for. */
static char *
wiki_save_raw (WikiCtx *ctx, const char *html)
{
    guint idx = ctx->saved->len;
    g_ptr_array_add (ctx->saved, g_strdup (html));
    return g_strdup_printf ("\x01%u\x01", idx);
}

/* HTML-escape <, >, & in user text.  Returned string is g_strdup-owned. */
static char *
wiki_quote_html (const char *src)
{
    GString *s = g_string_sized_new (strlen (src) + 16);
    for (const char *p = src; *p; p++)
    {
        switch (*p)
        {
            case '&': g_string_append (s, "&amp;"); break;
            case '<': g_string_append (s, "&lt;");  break;
            case '>': g_string_append (s, "&gt;");  break;
            default:  g_string_append_c (s, *p);    break;
        }
    }
    return g_string_free (s, FALSE);
}

/* Extract `<tag>...</tag>` blocks (case-insensitive) from `src`,
 * replace each with a saved-placeholder, and append the saved chunk
 * to `ctx->saved`.  `wrap_with` (e.g. "pre") wraps each chunk in
 * <wrap_with>...</wrap_with> before saving; NULL means keep literal.
 * Operates on a copy of src; returns a fresh string. */
static char *
wiki_extract_block (WikiCtx *ctx, const char *src,
                    const char *tag, const char *wrap_with)
{
    GString *out      = g_string_sized_new (strlen (src));
    char    *open_tag = g_strdup_printf ("<%s>", tag);
    char    *close_tag = g_strdup_printf ("</%s>", tag);
    gsize    open_len  = strlen (open_tag);
    gsize    close_len = strlen (close_tag);
    const char *p = src;

    while (*p)
    {
        /* Case-insensitive match for <tag>. */
        if (g_ascii_strncasecmp (p, open_tag, open_len) == 0)
        {
            const char *body  = p + open_len;
            const char *end   = body;
            while (*end && g_ascii_strncasecmp (end, close_tag, close_len) != 0)
                end++;
            if (*end)
            {
                gsize body_len = end - body;
                char *inner    = g_strndup (body, body_len);
                char *to_save;
                char *placeholder;
                if (wrap_with)
                    to_save = g_strdup_printf ("<%s>%s</%s>",
                                               wrap_with, inner, wrap_with);
                else
                    to_save = g_strdup (inner);
                placeholder = wiki_save_raw (ctx, to_save);
                g_string_append (out, placeholder);
                g_free (placeholder);
                g_free (to_save);
                g_free (inner);
                p = end + close_len;
                continue;
            }
        }
        g_string_append_c (out, *p++);
    }

    g_free (open_tag);
    g_free (close_tag);
    return g_string_free (out, FALSE);
}

/* Restore "\x01<N>\x01" placeholders with the stored chunks.  Loops
 * until no more substitutions happen so nested placeholders work. */
static char *
wiki_restore_saved (WikiCtx *ctx, char *text)
{
    GString *out;
    gboolean changed;

    do
    {
        changed = FALSE;
        out = g_string_sized_new (strlen (text));
        for (const char *p = text; *p; )
        {
            if (*p == '\x01')
            {
                const char *q = p + 1;
                guint idx = 0;
                while (*q >= '0' && *q <= '9')
                {
                    idx = idx * 10 + (*q - '0');
                    q++;
                }
                if (*q == '\x01' && idx < ctx->saved->len)
                {
                    g_string_append (out, (const char *) ctx->saved->pdata[idx]);
                    p = q + 1;
                    changed = TRUE;
                    continue;
                }
            }
            g_string_append_c (out, *p++);
        }
        g_free (text);
        text = g_string_free (out, FALSE);
    } while (changed);

    return text;
}

/* Inline rule helpers — these all return a fresh g_strdup'd string. */

/* Replace runs of delim..delim with <open>...</open>.  Non-greedy by
 * matching the nearest closing delim.  delim_len must be ≥1.  Used
 * for ''italic'' / '''bold''' / `code`. */
static char *
wiki_apply_pair (const char *src, const char *delim, gsize delim_len,
                 const char *open_tag, const char *close_tag)
{
    GString    *out = g_string_sized_new (strlen (src));
    const char *p   = src;

    while (*p)
    {
        if (strncmp (p, delim, delim_len) == 0)
        {
            const char *body = p + delim_len;
            const char *end  = strstr (body, delim);
            if (end && end > body)
            {
                g_string_append (out, open_tag);
                g_string_append_len (out, body, end - body);
                g_string_append (out, close_tag);
                p = end + delim_len;
                continue;
            }
        }
        g_string_append_c (out, *p++);
    }
    return g_string_free (out, FALSE);
}

/* Match a URL starting at *p* and return the byte length of the
 * scheme+rest, or 0 if it's not a recognised URL.  Habitat accepts
 * "scheme:" followed by any non-space/bracket characters (so e.g.
 * "http:?Home" and "Local:Page" are valid even without "//"). */
static gsize
wiki_match_url (const char *p)
{
    static const char *schemes[] = {
        "http",  "https", "ftp",   "ftps",   "file",
        "mailto","news",  "nntp",  "gopher", "telnet",
        "wais",  "afs",   "mid",   "cid",    "prospero",
        NULL
    };
    for (int i = 0; schemes[i]; i++)
    {
        gsize slen = strlen (schemes[i]);
        if (g_ascii_strncasecmp (p, schemes[i], slen) == 0
            && p[slen] == ':')
        {
            const char *end = p + slen + 1;
            while (*end && *end != ' ' && *end != '\t' && *end != '\n'
                   && *end != '<' && *end != '>' && *end != '"'
                   && *end != ']' && *end != '|' && *end != '\x01')
                end++;
            /* Trim trailing punctuation that's usually sentence noise. */
            while (end > p + slen + 1
                   && strchr (".,;:)!?", end[-1]))
                end--;
            return end - p;
        }
    }
    return 0;
}

/* WikiWord = uppercase+ lowercase+ uppercase letter+ rest.
 * Returns matched byte length or 0. */
static gsize
wiki_match_wikiword (const char *p)
{
    const char *q = p;
    int upper_run = 0, lower_run = 0;
    while (g_ascii_isupper (*q)) { q++; upper_run++; }
    if (upper_run < 1) return 0;
    while (g_ascii_islower (*q)) { q++; lower_run++; }
    if (lower_run < 1) return 0;
    if (!g_ascii_isupper (*q)) return 0;
    while (g_ascii_isalnum (*q)) q++;
    return q - p;
}

/* Apply all inline rules to `text` (which has already been HTML-escaped).
 * Returns a fresh g_strdup'd string with rich HTML markup interspersed.
 * Links and other "complex" outputs are wrapped in save-raw placeholders
 * so subsequent passes (bold/italic/wikiword) don't re-mangle them. */
static char *
wiki_inline (WikiCtx *ctx, const char *text)
{
    GString    *out = g_string_sized_new (strlen (text) + 32);
    const char *p   = text;

    /* Pass 1: URLs, [[FreeLinks]], [url text] brackets — stash each
     * generated <a> tag in saved/ so later inline passes don't see it.
     * Walk char-by-char looking for the starts of these constructs. */
    while (*p)
    {
        /* Named anchor: [#Anchor] (Habitat NamedAnchors).  Emits an
         * empty <a name="..."> in place so later [[Page#Anchor]] /
         * [url#Anchor] references resolve to it within the rendered
         * preview.  Doesn't show any visible glyph.  Duplicate uses of
         * the same name silently drop the second/third anchor so we
         * don't trip libxml2's "ID already defined" warning. */
        if (p[0] == '[' && p[1] == '#')
        {
            const char *body  = p + 2;
            const char *close = strchr (body, ']');
            if (close && close > body)
            {
                char *name = g_strndup (body, close - body);
                if (!g_hash_table_contains (ctx->anchors_seen, name))
                {
                    char *raw = g_strdup_printf ("<a name=\"%s\"></a>", name);
                    char *ph  = wiki_save_raw (ctx, raw);
                    g_string_append (out, ph);
                    g_free (ph); g_free (raw);
                    g_hash_table_add (ctx->anchors_seen,
                                       g_strdup (name));
                }
                g_free (name);
                p = close + 1;
                continue;
            }
        }

        /* [[Page]] or [[Page|text]] */
        if (p[0] == '[' && p[1] == '[')
        {
            const char *body  = p + 2;
            const char *close = strstr (body, "]]");
            if (close)
            {
                gsize       body_len = close - body;
                char       *content  = g_strndup (body, body_len);
                const char *bar      = strchr (content, '|');
                char       *href, *label, *anchor;
                if (bar)
                {
                    href  = g_strndup (content, bar - content);
                    label = g_strdup (bar + 1);
                }
                else
                {
                    href  = g_strdup (content);
                    label = g_strdup (content);
                }
                anchor = g_strdup_printf ("<a href=\"%s\">%s</a>", href, label);
                {
                    char *ph = wiki_save_raw (ctx, anchor);
                    g_string_append (out, ph);
                    g_free (ph);
                }
                g_free (anchor);
                g_free (href);
                g_free (label);
                g_free (content);
                p = close + 2;
                continue;
            }
        }

        /* [url ...]   or  [url]  */
        if (p[0] == '[')
        {
            gsize ulen = wiki_match_url (p + 1);
            if (ulen > 0)
            {
                const char *url_start = p + 1;
                const char *after_url = url_start + ulen;
                const char *close     = strchr (after_url, ']');
                if (close)
                {
                    char *href = g_strndup (url_start, ulen);
                    const char *text_start = after_url;
                    while (*text_start == ' ' || *text_start == '\t')
                        text_start++;
                    char *anchor;
                    if (text_start < close)
                    {
                        char *label = g_strndup (text_start, close - text_start);
                        anchor = g_strdup_printf ("<a href=\"%s\">%s</a>",
                                                  href, label);
                        g_free (label);
                    }
                    else
                    {
                        ctx->link_counter++;
                        anchor = g_strdup_printf ("<a href=\"%s\">[%d]</a>",
                                                  href, ctx->link_counter);
                    }
                    {
                        char *ph = wiki_save_raw (ctx, anchor);
                        g_string_append (out, ph);
                        g_free (ph);
                    }
                    g_free (anchor);
                    g_free (href);
                    p = close + 1;
                    continue;
                }
            }
        }

        /* Bare URL — must be at word boundary (or start of buffer) */
        if (p == text || !g_ascii_isalnum (p[-1]))
        {
            gsize ulen = wiki_match_url (p);
            if (ulen > 0)
            {
                char *href = g_strndup (p, ulen);
                char *anchor = g_strdup_printf ("<a href=\"%s\">%s</a>",
                                                href, href);
                char *ph = wiki_save_raw (ctx, anchor);
                g_string_append (out, ph);
                g_free (ph);
                g_free (anchor);
                g_free (href);
                p += ulen;
                continue;
            }
        }

        /* WikiWord — must be at word boundary */
        if (p == text || !g_ascii_isalnum (p[-1]))
        {
            gsize wlen = wiki_match_wikiword (p);
            if (wlen > 0)
            {
                char *word   = g_strndup (p, wlen);
                char *anchor = g_strdup_printf ("<a href=\"%s\">%s</a>",
                                                word, word);
                char *ph     = wiki_save_raw (ctx, anchor);
                g_string_append (out, ph);
                g_free (ph);
                g_free (anchor);
                g_free (word);
                p += wlen;
                continue;
            }
        }

        g_string_append_c (out, *p++);
    }

    /* Pass 2: HTML passthrough for the inline tags users actually
     * write inline (Habitat's @HtmlPairs whitelist).  After Phase-2's
     * global HTML-escape these reach us as "&lt;u&gt;text&lt;/u&gt;"
     * etc.; rewrite each pair back to a real tag so MooHtml renders
     * the underline / monospace / etc. visually.  Unknown tags stay
     * escaped (so a stray "<foo>" shows literally rather than being
     * dropped). */
    char *stage = g_string_free (out, FALSE);
    {
        static const char *pairs[] = {
            "b", "i", "u", "s",
            "strong", "em", "strike",
            "code", "tt", "kbd", "var",
            "sub", "sup", "mark", "cite", "q",
            "abbr", "small", "big",
            NULL
        };
        for (int i = 0; pairs[i]; i++)
        {
            char *open_pat  = g_strdup_printf ("&lt;%s&gt;",   pairs[i]);
            char *close_pat = g_strdup_printf ("&lt;/%s&gt;",  pairs[i]);
            char *open_rep  = g_strdup_printf ("<%s>",          pairs[i]);
            char *close_rep = g_strdup_printf ("</%s>",         pairs[i]);

            /* Manual scan: replace open_pat..close_pat with the real
             * tag pair.  Non-greedy match — the nearest close_pat wins.
             * wiki_apply_pair won't do it because it expects the
             * opening and closing delimiters to be identical. */
            GString *next = g_string_sized_new (strlen (stage));
            const char *q = stage;
            gsize open_len  = strlen (open_pat);
            gsize close_len = strlen (close_pat);
            while (*q)
            {
                if (strncmp (q, open_pat, open_len) == 0)
                {
                    const char *body = q + open_len;
                    const char *end  = strstr (body, close_pat);
                    if (end && end > body)
                    {
                        g_string_append (next, open_rep);
                        g_string_append_len (next, body, end - body);
                        g_string_append (next, close_rep);
                        q = end + close_len;
                        continue;
                    }
                }
                g_string_append_c (next, *q++);
            }
            g_free (stage);
            stage = g_string_free (next, FALSE);

            g_free (open_pat); g_free (close_pat);
            g_free (open_rep); g_free (close_rep);
        }
    }

    /* Pass 3: quote markup.  5-quote first (so it doesn't get mangled
     * by the 3- and 2-quote passes), then 3-quote bold, then 2-quote
     * italic, then 1-back-quote inline code.  This is the same
     * 5-then-3-then-2 order Habitat's CommonMarkup achieves with its
     * leading-quote-greedy regex. */
    char *boldit = wiki_apply_pair (stage, "'''''", 5,
                                    "<em><strong>", "</strong></em>");
    g_free (stage);
    char *bold = wiki_apply_pair (boldit, "'''", 3, "<strong>", "</strong>");
    g_free (boldit);
    char *italic = wiki_apply_pair (bold, "''", 2, "<em>", "</em>");
    g_free (bold);
    char *code = wiki_apply_pair (italic, "`", 1, "<code>", "</code>");
    g_free (italic);

    return code;
}

/* Close blocks until depth reaches `target`.  Block stack is FIFO from
 * outermost to innermost; we pop the top until we hit the target. */
static void
wiki_close_to_depth (WikiCtx *ctx, int target)
{
    while (g_slist_length (ctx->blocks) > (guint) target)
    {
        char *tag = (char *) ctx->blocks->data;
        ctx->blocks = g_slist_delete_link (ctx->blocks, ctx->blocks);
        g_string_append_printf (ctx->out, "</%s>\n", tag);
        g_free (tag);
        g_array_remove_index (ctx->block_depth,
                              ctx->block_depth->len - 1);
    }
}

/* Close every open block (used at end of input and on blank lines). */
static void
wiki_close_all_blocks (WikiCtx *ctx)
{
    if (ctx->in_para)
    {
        g_string_append (ctx->out, "</p>\n");
        ctx->in_para = FALSE;
    }
    wiki_close_to_depth (ctx, 0);
}

/* Push a new block (open the tag, push the stack entries). */
static void
wiki_open_block (WikiCtx *ctx, const char *tag, int depth)
{
    g_string_append_printf (ctx->out, "<%s>\n", tag);
    ctx->blocks = g_slist_append (ctx->blocks, g_strdup (tag));
    g_array_append_val (ctx->block_depth, depth);
}

/* Reconcile current block stack with the desired (kind,depth) stack
 * implied by the new line.  Close mismatched blocks and open new ones
 * as needed.  `kind` is the inner tag (ul/ol/dl); we open one block
 * per depth level so nested lists render correctly. */
static void
wiki_match_list_depth (WikiCtx *ctx, const char *kind, int depth)
{
    /* Close anything that doesn't share the kind at its depth. */
    guint i = 0;
    GSList *l = ctx->blocks;
    while (l && i < (guint) depth)
    {
        const char *cur = (const char *) l->data;
        if (strcmp (cur, kind) != 0)
        {
            wiki_close_to_depth (ctx, i);
            break;
        }
        l = l->next;
        i++;
    }
    /* Close deeper levels regardless. */
    wiki_close_to_depth (ctx, depth - 0);
    /* But we want exactly `depth` blocks of `kind` open. */
    if ((int) g_slist_length (ctx->blocks) > depth)
        wiki_close_to_depth (ctx, depth);
    while ((int) g_slist_length (ctx->blocks) < depth)
        wiki_open_block (ctx, kind, g_slist_length (ctx->blocks) + 1);
}

/* Emit a single line's content, with paragraph wrapping and inline
 * rules applied.  Caller has already classified the line as plain
 * paragraph text. */
static void
wiki_emit_paragraph_line (WikiCtx *ctx, const char *line)
{
    char *inlined = wiki_inline (ctx, line);
    if (!ctx->in_para)
    {
        g_string_append (ctx->out, "<p>");
        ctx->in_para = TRUE;
    }
    else
    {
        g_string_append (ctx->out, " ");
    }
    g_string_append (ctx->out, inlined);
    g_free (inlined);
}

/* Process one line.  Caller passes the HTML-escaped line text (without
 * trailing newline).  Determines block type, manages the stack, emits
 * the line's content. */
static void
wiki_process_line (WikiCtx *ctx, const char *line)
{
    /* Blank line — end paragraph, close transient blocks (pre/table).
     * Lists/dl stay open across blank-line gaps? Habitat closes them;
     * we close everything for simplicity. */
    if (line[0] == '\0')
    {
        wiki_close_all_blocks (ctx);
        return;
    }

    /* ---- <toc> marker on its own line — handled as a block so it
     * doesn't get wrapped in <p> (which would make libxml2 reject the
     * generated nested-list TOC).  After Phase 2 the marker reaches
     * us as "&lt;toc&gt;"; replace it with a sentinel that survives
     * the rest of the pipeline and gets expanded in Phase 5. */
    {
        const char *q = line;
        while (*q == ' ' || *q == '\t') q++;
        if (g_ascii_strncasecmp (q, "&lt;toc&gt;", 11) == 0)
        {
            const char *tail = q + 11;
            while (*tail == ' ' || *tail == '\t') tail++;
            if (*tail == '\0')
            {
                wiki_close_all_blocks (ctx);
                g_string_append (ctx->out, "\x01TOC\x01\n");
                return;
            }
        }
    }

    /* ---- Horizontal rule ---- */
    if (line[0] == '-' && line[1] == '-' && line[2] == '-' && line[3] == '-')
    {
        gboolean all_dash = TRUE;
        for (const char *p = line; *p; p++)
            if (*p != '-') { all_dash = FALSE; break; }
        if (all_dash)
        {
            wiki_close_all_blocks (ctx);
            g_string_append (ctx->out, "<hr>\n");
            return;
        }
    }

    /* ---- Heading: = title = up to ====== title ====== ---- */
    if (line[0] == '=')
    {
        int level = 0;
        const char *p = line;
        while (*p == '=' && level < 6) { p++; level++; }
        if (level >= 1 && *p == ' ')
        {
            /* Find the matching =s at the tail */
            const char *end = line + strlen (line);
            const char *tail = end;
            while (tail > p && tail[-1] == ' ') tail--;
            int tail_eq = 0;
            while (tail > p && tail[-1] == '=' && tail_eq < level)
            {
                tail--;
                tail_eq++;
            }
            if (tail_eq == level && tail > p + 1)
            {
                wiki_close_all_blocks (ctx);
                /* Skip leading space after opening = */
                const char *title_start = p + 1;
                /* Trim trailing spaces */
                const char *title_end = tail;
                while (title_end > title_start
                       && title_end[-1] == ' ')
                    title_end--;
                char *title = g_strndup (title_start,
                                          title_end - title_start);

                /* Habitat convention: a leading "#" after the opening
                 * equals signs ("== # Heading ==") marks this heading
                 * as TOC-worthy AND creates a named anchor for it.
                 * Strip the "#" + spaces from the display title, and
                 * record an entry in ctx->toc that will be replayed
                 * when wiki_to_html post-processes <toc> markers. */
                gboolean in_toc = FALSE;
                char *display = title;
                if (display[0] == '#'
                    && (display[1] == ' ' || display[1] == '\t'
                        || display[1] == '\0'))
                {
                    in_toc = TRUE;
                    display = title + 1;
                    while (*display == ' ' || *display == '\t')
                        display++;
                }

                char *anchor = NULL;
                if (in_toc)
                {
                    anchor = wiki_slugify (display);
                    if (!anchor)
                        anchor = g_strdup_printf ("section-%d",
                                                   ctx->anchor_seq);
                    ctx->anchor_seq++;

                    WikiTocEntry *e = g_new0 (WikiTocEntry, 1);
                    e->level  = level;
                    e->title  = g_strdup (display);
                    e->anchor = g_strdup (anchor);
                    g_ptr_array_add (ctx->toc, e);
                }

                char *inlined = wiki_inline (ctx, display);
                if (anchor)
                {
                    /* Skip the <a name> if a previous heading or
                     * inline [#anchor] already registered this name. */
                    if (g_hash_table_contains (ctx->anchors_seen, anchor))
                    {
                        g_string_append_printf (ctx->out,
                            "<h%d>%s</h%d>\n", level, inlined, level);
                    }
                    else
                    {
                        g_string_append_printf (ctx->out,
                            "<h%d><a name=\"%s\"></a>%s</h%d>\n",
                            level, anchor, inlined, level);
                        g_hash_table_add (ctx->anchors_seen,
                                           g_strdup (anchor));
                    }
                }
                else
                    g_string_append_printf (ctx->out, "<h%d>%s</h%d>\n",
                                             level, inlined, level);
                g_free (inlined);
                g_free (anchor);
                g_free (title);
                return;
            }
        }
    }

    /* ---- Unordered list (*) and ordered list (#) ---- */
    if (line[0] == '*' || line[0] == '#')
    {
        char ch    = line[0];
        int  depth = 0;
        const char *p = line;
        while (*p == ch) { p++; depth++; }
        if (depth >= 1 && (*p == ' ' || *p == '\t' || *p == '\0'))
        {
            const char *content = p;
            while (*content == ' ' || *content == '\t') content++;
            if (ctx->in_para) {
                g_string_append (ctx->out, "</p>\n");
                ctx->in_para = FALSE;
            }
            wiki_match_list_depth (ctx, ch == '*' ? "ul" : "ol", depth);
            char *inlined = wiki_inline (ctx, content);
            g_string_append_printf (ctx->out, "<li>%s</li>\n", inlined);
            g_free (inlined);
            return;
        }
    }

    /* ---- Definition list: ; term : def ---- */
    if (line[0] == ';')
    {
        int depth = 0;
        const char *p = line;
        while (*p == ';') { p++; depth++; }
        const char *colon = strchr (p, ':');
        if (colon)
        {
            char *term = g_strndup (p, colon - p);
            char *def  = g_strdup (colon + 1);
            char *t    = wiki_inline (ctx, g_strstrip (term));
            char *d    = wiki_inline (ctx, g_strstrip (def));
            if (ctx->in_para) {
                g_string_append (ctx->out, "</p>\n");
                ctx->in_para = FALSE;
            }
            wiki_match_list_depth (ctx, "dl", depth);
            g_string_append_printf (ctx->out, "<dt>%s</dt><dd>%s</dd>\n",
                                     t, d);
            g_free (t); g_free (d); g_free (term); g_free (def);
            return;
        }
    }

    /* ---- Indented (: text) ---- */
    if (line[0] == ':')
    {
        int depth = 0;
        const char *p = line;
        while (*p == ':') { p++; depth++; }
        char *inlined = wiki_inline (ctx, p);
        if (ctx->in_para) {
            g_string_append (ctx->out, "</p>\n");
            ctx->in_para = FALSE;
        }
        wiki_match_list_depth (ctx, "dl", depth);
        g_string_append_printf (ctx->out, "<dd>%s</dd>\n", inlined);
        g_free (inlined);
        return;
    }

    /* ---- Table row: ||cell||cell||  or  !!cell!!cell!! ---- */
    if ((line[0] == '|' && line[1] == '|')
        || (line[0] == '!' && line[1] == '!'))
    {
        const char  *sep  = (line[0] == '|') ? "||" : "!!";
        const char  *cell_tag = (line[0] == '|') ? "td" : "th";
        gsize        sep_len = 2;
        const char  *p = line + sep_len;
        if (ctx->in_para) {
            g_string_append (ctx->out, "</p>\n");
            ctx->in_para = FALSE;
        }
        /* Open <table> if not already in one */
        if (!ctx->blocks || strcmp ((char *) ctx->blocks->data, "table") != 0)
        {
            wiki_close_all_blocks (ctx);
            wiki_open_block (ctx, "table", 1);
        }
        g_string_append (ctx->out, "<tr>");
        while (*p)
        {
            const char *end = strstr (p, sep);
            if (!end) end = p + strlen (p);
            char *cell    = g_strndup (p, end - p);
            char *trimmed = g_strstrip (cell);
            char *inlined = wiki_inline (ctx, trimmed);
            g_string_append_printf (ctx->out, "<%s>%s</%s>",
                                     cell_tag, inlined, cell_tag);
            g_free (inlined);
            g_free (cell);
            if (*end == '\0') break;
            p = end + sep_len;
            /* trailing empty cell after final sep? skip */
            if (*p == '\0' || (*p == ' ' && !*(p + 1))) break;
        }
        g_string_append (ctx->out, "</tr>\n");
        return;
    }

    /* ---- Preformatted (leading space or tab) ---- */
    if (line[0] == ' ' || line[0] == '\t')
    {
        if (ctx->in_para) {
            g_string_append (ctx->out, "</p>\n");
            ctx->in_para = FALSE;
        }
        if (!ctx->blocks || strcmp ((char *) ctx->blocks->data, "pre") != 0)
        {
            wiki_close_all_blocks (ctx);
            wiki_open_block (ctx, "pre", 1);
        }
        g_string_append (ctx->out, line);
        g_string_append_c (ctx->out, '\n');
        return;
    }

    /* ---- Default: paragraph text ---- */
    /* If we were in a non-paragraph block, close it first. */
    if (ctx->blocks && strcmp ((char *) ctx->blocks->data, "pre") == 0)
        wiki_close_all_blocks (ctx);
    if (ctx->blocks
        && (strcmp ((char *) ctx->blocks->data, "table") == 0))
        wiki_close_all_blocks (ctx);
    wiki_emit_paragraph_line (ctx, line);
}

/* Top-level converter.  Returns g_strdup'd HTML (caller frees). */
static char *
wiki_to_html (const char *src)
{
    WikiCtx ctx = { 0 };
    ctx.out          = g_string_sized_new (strlen (src) * 2 + 64);
    ctx.saved        = g_ptr_array_new_with_free_func (g_free);
    ctx.blocks       = NULL;
    ctx.block_depth  = g_array_new (FALSE, FALSE, sizeof (int));
    ctx.in_para      = FALSE;
    ctx.link_counter = 0;
    ctx.toc          = g_ptr_array_new_with_free_func (wiki_toc_entry_free);
    ctx.anchor_seq   = 1;
    ctx.anchors_seen = g_hash_table_new_full (g_str_hash, g_str_equal,
                                               g_free, NULL);

    /* Phase 1: pull out protected regions BEFORE HTML-escaping.  These
     * are the only places where we honour literal HTML; everything else
     * goes through wiki_quote_html. */
    char *step1 = wiki_extract_block (&ctx, src, "nowiki", NULL);
    char *step2 = wiki_extract_block (&ctx, step1, "pre", "pre");
    g_free (step1);
    char *step3 = wiki_extract_block (&ctx, step2, "code", "pre");
    g_free (step2);

    /* Phase 2: HTML-escape everything else.  Placeholders are pure ASCII
     * (\x01<digits>\x01) so they survive quoting. */
    char *escaped = wiki_quote_html (step3);
    g_free (step3);

    /* Phase 2.5: line continuation — backslash at end of line joins
     * with the next line as a single logical line.  Done in-place on
     * the escaped buffer before the line split. */
    {
        GString *joined = g_string_sized_new (strlen (escaped));
        for (const char *p = escaped; *p; p++)
        {
            if (*p == '\\' && p[1] == '\n')
            {
                g_string_append_c (joined, ' ');
                p++;       /* swallow the newline */
            }
            else
            {
                g_string_append_c (joined, *p);
            }
        }
        g_free (escaped);
        escaped = g_string_free (joined, FALSE);
    }

    /* Phase 3: line-by-line block processing. */
    char **lines = g_strsplit (escaped, "\n", -1);
    g_free (escaped);
    for (char **l = lines; *l; l++)
        wiki_process_line (&ctx, *l);
    g_strfreev (lines);

    wiki_close_all_blocks (&ctx);

    /* Phase 4: restore protected regions. */
    char *result = g_string_free (ctx.out, FALSE);
    result = wiki_restore_saved (&ctx, result);

    /* Phase 5: build the TOC and splice it in at the \x01TOC\x01
     * sentinels left behind by the line processor.  Nested-list HTML
     * has to wrap inner <ul>s inside the previous <li> (HTML5 doesn't
     * accept <ul> as a direct child of <ul>), which makes building it
     * from a flat (level, title) list mildly awkward — see the
     * deferred-close state machine below. */
    {
        GString *toc = g_string_new (NULL);
        if (ctx.toc->len == 0)
        {
            g_string_append (toc,
                "<div class=\"wiki-toc\"><em>"
                "(no headings marked for the table of contents — use "
                "<code>== # Title ==</code>)</em></div>\n");
        }
        else
        {
            int      depth   = 0;
            gboolean li_open = FALSE;
            g_string_append (toc,
                "<div class=\"wiki-toc\"><b>Contents</b>\n");
            for (guint i = 0; i < ctx.toc->len; i++)
            {
                WikiTocEntry *e = (WikiTocEntry *) ctx.toc->pdata[i];

                /* Pop deeper levels. */
                while (depth > e->level)
                {
                    if (li_open)
                    {
                        g_string_append (toc, "</li>\n");
                        li_open = FALSE;
                    }
                    g_string_append (toc, "</ul>\n");
                    depth--;
                    if (depth > 0)
                        g_string_append (toc, "</li>\n");
                }

                /* Push to entry's level.  Deeper <ul>s nest inside the
                 * currently-open <li>; if there's no open <li> at this
                 * depth (e.g. document starts at H3 with no H2) we
                 * insert a placeholder <li> as wrapper. */
                while (depth < e->level)
                {
                    if (li_open)
                    {
                        g_string_append (toc, "<ul>\n");
                        li_open = FALSE;
                    }
                    else if (depth == 0)
                        g_string_append (toc, "<ul>\n");
                    else
                        g_string_append (toc, "<li><ul>\n");
                    depth++;
                }

                /* Close any previous sibling <li> at this level. */
                if (li_open)
                    g_string_append (toc, "</li>\n");
                g_string_append_printf (toc,
                    "<li><a href=\"#%s\">%s</a>",
                    e->anchor, e->title);
                li_open = TRUE;
            }
            if (li_open)
                g_string_append (toc, "</li>\n");
            while (depth > 0)
            {
                g_string_append (toc, "</ul>\n");
                depth--;
                if (depth > 0)
                    g_string_append (toc, "</li>\n");
            }
            g_string_append (toc, "</div>\n");
        }

        /* Replace each "\x01TOC\x01" sentinel with the rendered TOC.
         * The sentinel was emitted as a block (not inside <p>) so the
         * inner <div>/<ul> aren't trapped in an inline context. */
        GString *out2 = g_string_sized_new (strlen (result) + toc->len);
        for (const char *p = result; *p; )
        {
            if (strncmp (p, "\x01TOC\x01", 5) == 0)
            {
                g_string_append (out2, toc->str);
                p += 5;
            }
            else
                g_string_append_c (out2, *p++);
        }
        g_string_free (toc, TRUE);
        g_free (result);
        result = g_string_free (out2, FALSE);
    }

    g_ptr_array_free (ctx.saved, TRUE);
    g_ptr_array_free (ctx.toc, TRUE);
    g_hash_table_destroy (ctx.anchors_seen);
    g_array_free (ctx.block_depth, TRUE);
    g_slist_free_full (ctx.blocks, g_free);
    return result;
}

/* ════════════════════════════════════════════════════════════════════════
 * Plugin lifecycle (mirrors moomarkdown.cpp closely)
 * ════════════════════════════════════════════════════════════════════════
 */

static void
wiki_render (WikiWindowPlugin *plugin, MooEditView *view_hint)
{
    MooEditWindow *window;
    MooEditView   *view;
    GtkTextBuffer *buffer;
    GtkTextIter    start, end;
    char          *wiki;
    char          *html;
    GString       *wrapped;

    if (plugin == NULL || plugin->html_view == NULL)
        return;

    window = MOO_WIN_PLUGIN (plugin)->window;
    view   = view_hint ? view_hint : moo_edit_window_get_active_view (window);
    if (view == NULL)
        return;

    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
    gtk_text_buffer_get_bounds (buffer, &start, &end);
    wiki = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
    if (wiki == NULL)
        return;

    html = wiki_to_html (wiki);
    g_free (wiki);

    /* MooHtml expects a complete document; wrap our body fragment. */
    wrapped = g_string_sized_new (strlen (html) + 32);
    g_string_append (wrapped, "<html><body>");
    g_string_append (wrapped, html);
    g_string_append (wrapped, "</body></html>");
    g_free (html);

    _moo_html_load_memory (GTK_TEXT_VIEW (plugin->html_view),
                           wrapped->str, wrapped->len, NULL, "UTF-8");
    g_string_free (wrapped, TRUE);
}

static gboolean
wiki_render_timeout (gpointer data)
{
    WikiWindowPlugin *plugin = (WikiWindowPlugin *) data;
    plugin->render_timeout_id = 0;
    wiki_render (plugin, NULL);
    return G_SOURCE_REMOVE;
}

static void
wiki_on_buffer_changed (G_GNUC_UNUSED GtkTextBuffer *buffer, gpointer data)
{
    WikiWindowPlugin *plugin = (WikiWindowPlugin *) data;
    if (plugin->render_timeout_id != 0)
        g_source_remove (plugin->render_timeout_id);
    plugin->render_timeout_id =
        g_timeout_add (WIKI_DEBOUNCE_MS, wiki_render_timeout, plugin);
}

static void
wiki_rewire_buffer_signal (WikiWindowPlugin *plugin)
{
    MooEditWindow *window = MOO_WIN_PLUGIN (plugin)->window;
    MooEditView   *view;
    GtkTextBuffer *buffer = NULL;

    view = moo_edit_window_get_active_view (window);
    if (view != NULL)
        buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

    if (plugin->current_buffer && plugin->buffer_changed_id)
    {
        g_signal_handler_disconnect (plugin->current_buffer,
                                     plugin->buffer_changed_id);
        plugin->buffer_changed_id = 0;
    }
    plugin->current_buffer = buffer;
    if (buffer != NULL)
        plugin->buffer_changed_id = g_signal_connect (
            buffer, "changed", G_CALLBACK (wiki_on_buffer_changed), plugin);
}

static void
wiki_on_active_doc_notify (G_GNUC_UNUSED GObject *window,
                            G_GNUC_UNUSED GParamSpec *pspec,
                            gpointer data)
{
    WikiWindowPlugin *plugin = (WikiWindowPlugin *) data;
    wiki_rewire_buffer_signal (plugin);
    wiki_render (plugin, NULL);
}

static gboolean
wiki_window_plugin_create (WikiWindowPlugin *plugin)
{
    MooEditWindow *window = MOO_WIN_PLUGIN (plugin)->window;
    GtkWidget     *scroll, *html;
    MooPaneLabel  *label;

    html = (GtkWidget *) g_object_new (MOO_TYPE_HTML, NULL);
    gtk_text_view_set_editable      (GTK_TEXT_VIEW (html), FALSE);
    gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (html), FALSE);
    gtk_text_view_set_wrap_mode      (GTK_TEXT_VIEW (html), GTK_WRAP_WORD_CHAR);
    gtk_widget_set_size_request      (html, 360, -1);

    /* Same 120% font bump as markdown preview. */
    {
        static GtkCssProvider *fp = NULL;
        if (fp == NULL)
        {
            fp = gtk_css_provider_new ();
            gtk_css_provider_load_from_data (
                fp, "textview { font-size: 120%; }", -1, NULL);
        }
        gtk_style_context_add_provider (
            gtk_widget_get_style_context (html),
            GTK_STYLE_PROVIDER (fp),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    }

    gtk_text_view_set_pixels_above_lines (GTK_TEXT_VIEW (html), 3);
    gtk_text_view_set_pixels_below_lines (GTK_TEXT_VIEW (html), 3);
    gtk_text_view_set_pixels_inside_wrap (GTK_TEXT_VIEW (html), 2);
    gtk_text_view_set_left_margin   (GTK_TEXT_VIEW (html), 10);
    gtk_text_view_set_right_margin  (GTK_TEXT_VIEW (html), 10);
    gtk_text_view_set_top_margin    (GTK_TEXT_VIEW (html), 8);
    gtk_text_view_set_bottom_margin (GTK_TEXT_VIEW (html), 8);

    scroll = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scroll),
                                    GTK_POLICY_AUTOMATIC,
                                    GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scroll),
                                         GTK_SHADOW_IN);
    gtk_container_add (GTK_CONTAINER (scroll), html);
    gtk_widget_show_all (scroll);

    label = moo_pane_label_new ("text-x-generic", NULL,
                                _("Wiki Preview"),
                                _("Wiki Preview"));
    plugin->pane = moo_edit_window_add_pane (window,
                                             WIKI_PLUGIN_ID,
                                             scroll, label,
                                             MOO_PANE_POS_RIGHT);
    moo_pane_label_free (label);

    plugin->html_view = html;

    if (moo_prefs_get_bool (WIKI_SHOW_PREF))
        moo_edit_window_show_pane (window, WIKI_PLUGIN_ID);

    plugin->notify_active_doc_id = g_signal_connect (
        window, "notify::active-doc",
        G_CALLBACK (wiki_on_active_doc_notify), plugin);

    wiki_rewire_buffer_signal (plugin);
    wiki_render (plugin, NULL);
    return TRUE;
}

static void
wiki_window_plugin_destroy (WikiWindowPlugin *plugin)
{
    MooEditWindow *window = MOO_WIN_PLUGIN (plugin)->window;

    if (plugin->render_timeout_id != 0)
    {
        g_source_remove (plugin->render_timeout_id);
        plugin->render_timeout_id = 0;
    }
    if (plugin->current_buffer && plugin->buffer_changed_id)
    {
        g_signal_handler_disconnect (plugin->current_buffer,
                                     plugin->buffer_changed_id);
        plugin->buffer_changed_id = 0;
        plugin->current_buffer    = NULL;
    }
    if (plugin->notify_active_doc_id)
    {
        g_signal_handler_disconnect (window, plugin->notify_active_doc_id);
        plugin->notify_active_doc_id = 0;
    }
    moo_edit_window_remove_pane (window, WIKI_PLUGIN_ID);
    plugin->pane      = NULL;
    plugin->html_view = NULL;
}

static gboolean
wiki_plugin_init (G_GNUC_UNUSED WikiPlugin *plugin)
{
    moo_prefs_new_key_bool (WIKI_SHOW_PREF, TRUE);
    return TRUE;
}

static void
wiki_plugin_deinit (G_GNUC_UNUSED WikiPlugin *plugin)
{
}

MOO_PLUGIN_DEFINE_INFO (wiki,
                        "Wiki Preview",
                        "Live Wiki preview side pane",
                        "medit project",
                        MOO_VERSION)

MOO_WIN_PLUGIN_DEFINE (Wiki, wiki)

MOO_PLUGIN_DEFINE (Wiki, wiki,
                   NULL, NULL, NULL, NULL, NULL,
                   wiki_window_plugin_get_type (),
                   0)

#endif /* MOO_BUILD_WIKI */

extern "C" gboolean
_moo_wiki_plugin_init (void)
{
#ifdef MOO_BUILD_WIKI
    MooPluginParams params = { TRUE, TRUE };
    return moo_plugin_register (WIKI_PLUGIN_ID,
                                wiki_plugin_get_type (),
                                &wiki_plugin_info,
                                &params);
#else
    return FALSE;
#endif
}
