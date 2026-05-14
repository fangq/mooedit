#include <mooutils/mooglade.h>
#include <mooutils/mooi18n.h>
#include <gtk/gtk.h>

static const char _prefs_general_xml_glade_xml[] =
"<?xml version=\"1.0\"?>"
"<glade-interface>"
"<!-- interface-requires gtk+ 2.8 -->"
"<!-- interface-naming-policy toplevel-contextual -->"
"<widget class=\"GtkWindow\" id=\"window1\">"
"<child>"
"<widget class=\"GtkVBox\" id=\"PrefsGeneral\">"
"<property name=\"visible\">True</property>"
"<property name=\"border_width\">12</property>"
"<property name=\"spacing\">18</property>"
"<child>"
"<widget class=\"GtkVBox\" id=\"vbox21\">"
"<property name=\"visible\">True</property>"
"<property name=\"spacing\">6</property>"
"<child>"
"<widget class=\"GtkLabel\" id=\"label15\">"
"<property name=\"visible\">True</property>"
"<property name=\"xalign\">0</property>"
"<property name=\"label\" translatable=\"yes\">&lt;b&gt;Keyboard&lt;/b&gt;</property>"
"<property name=\"use_markup\">True</property>"
"</widget>"
"<packing>"
"<property name=\"expand\">False</property>"
"<property name=\"fill\">False</property>"
"<property name=\"position\">0</property>"
"</packing>"
"</child>"
"<child>"
"<widget class=\"GtkAlignment\" id=\"alignment11\">"
"<property name=\"visible\">True</property>"
"<property name=\"left_padding\">12</property>"
"<child>"
"<widget class=\"GtkVBox\" id=\"vbox22\">"
"<property name=\"visible\">True</property>"
"<property name=\"spacing\">6</property>"
"<child>"
"<widget class=\"GtkCheckButton\" id=\"smarthome\">"
"<property name=\"label\" translatable=\"yes\">Smart Home and End</property>"
"<property name=\"visible\">True</property>"
"<property name=\"can_focus\">False</property>"
"<property name=\"receives_default\">False</property>"
"<property name=\"use_underline\">True</property>"
"<property name=\"focus_on_click\">False</property>"
"<property name=\"draw_indicator\">True</property>"
"</widget>"
"<packing>"
"<property name=\"expand\">False</property>"
"<property name=\"fill\">False</property>"
"<property name=\"position\">0</property>"
"</packing>"
"</child>"
"<child>"
"<widget class=\"GtkCheckButton\" id=\"enable_auto_indent\">"
"<property name=\"visible\">True</property>"
"<property name=\"can_focus\">False</property>"
"<property name=\"receives_default\">False</property>"
"<property name=\"draw_indicator\">True</property>"
"<child>"
"<widget class=\"GtkLabel\" id=\"label16\">"
"<property name=\"visible\">True</property>"
"<property name=\"label\" translatable=\"yes\">Enable auto indentation</property>"
"</widget>"
"</child>"
"</widget>"
"<packing>"
"<property name=\"expand\">False</property>"
"<property name=\"fill\">False</property>"
"<property name=\"position\">1</property>"
"</packing>"
"</child>"
"<child>"
"<widget class=\"GtkCheckButton\" id=\"usespaces\">"
"<property name=\"label\" translatable=\"yes\">Do not use tabs for indentation</property>"
"<property name=\"visible\">True</property>"
"<property name=\"can_focus\">False</property>"
"<property name=\"receives_default\">False</property>"
"<property name=\"use_underline\">True</property>"
"<property name=\"focus_on_click\">False</property>"
"<property name=\"draw_indicator\">True</property>"
"</widget>"
"<packing>"
"<property name=\"expand\">False</property>"
"<property name=\"fill\">False</property>"
"<property name=\"position\">2</property>"
"</packing>"
"</child>"
"<child>"
"<widget class=\"GtkCheckButton\" id=\"backspace_indents\">"
"<property name=\"visible\">True</property>"
"<property name=\"can_focus\">False</property>"
"<property name=\"receives_default\">False</property>"
"<property name=\"draw_indicator\">True</property>"
"<child>"
"<widget class=\"GtkLabel\" id=\"label17\">"
"<property name=\"visible\">True</property>"
"<property name=\"label\" translatable=\"yes\">Backspace key unindents</property>"
"</widget>"
"</child>"
"</widget>"
"<packing>"
"<property name=\"position\">3</property>"
"</packing>"
"</child>"
"<child>"
"<widget class=\"GtkCheckButton\" id=\"tab_indents\">"
"<property name=\"visible\">True</property>"
"<property name=\"can_focus\">False</property>"
"<property name=\"receives_default\">False</property>"
"<property name=\"draw_indicator\">True</property>"
"<child>"
"<widget class=\"GtkLabel\" id=\"label18\">"
"<property name=\"visible\">True</property>"
"<property name=\"label\" translatable=\"yes\">Tab key indents</property>"
"</widget>"
"</child>"
"</widget>"
"<packing>"
"<property name=\"position\">4</property>"
"</packing>"
"</child>"
"<child>"
"<widget class=\"GtkTable\" id=\"table1\">"
"<property name=\"visible\">True</property>"
"<property name=\"n_rows\">2</property>"
"<property name=\"n_columns\">2</property>"
"<property name=\"column_spacing\">6</property>"
"<property name=\"row_spacing\">6</property>"
"<child>"
"<widget class=\"GtkSpinButton\" id=\"indent_width\">"
"<property name=\"visible\">True</property>"
"<property name=\"adjustment\">4 1 100 1 10 0</property>"
"<property name=\"climb_rate\">1</property>"
"<property name=\"numeric\">True</property>"
"</widget>"
"<packing>"
"<property name=\"left_attach\">1</property>"
"<property name=\"right_attach\">2</property>"
"<property name=\"top_attach\">1</property>"
"<property name=\"bottom_attach\">2</property>"
"<property name=\"x_options\"></property>"
"</packing>"
"</child>"
"<child>"
"<widget class=\"GtkLabel\" id=\"label32\">"
"<property name=\"visible\">True</property>"
"<property name=\"xalign\">1</property>"
"<property name=\"label\" translatable=\"yes\">Indent width:</property>"
"<property name=\"mnemonic_widget\">indent_width</property>"
"</widget>"
"<packing>"
"<property name=\"top_attach\">1</property>"
"<property name=\"bottom_attach\">2</property>"
"<property name=\"x_options\">GTK_FILL</property>"
"</packing>"
"</child>"
"<child>"
"<widget class=\"GtkSpinButton\" id=\"tab_width\">"
"<property name=\"visible\">True</property>"
"<property name=\"can_focus\">True</property>"
"<property name=\"adjustment\">8 1 100 1 10 0</property>"
"<property name=\"numeric\">True</property>"
"<property name=\"update_policy\">if-valid</property>"
"</widget>"
"<packing>"
"<property name=\"left_attach\">1</property>"
"<property name=\"right_attach\">2</property>"
"<property name=\"x_options\"></property>"
"</packing>"
"</child>"
"<child>"
"<widget class=\"GtkLabel\" id=\"label19\">"
"<property name=\"visible\">True</property>"
"<property name=\"xalign\">1</property>"
"<property name=\"label\" translatable=\"yes\">Tab width:</property>"
"<property name=\"mnemonic_widget\">tab_width</property>"
"</widget>"
"<packing>"
"<property name=\"x_options\">GTK_FILL</property>"
"</packing>"
"</child>"
"</widget>"
"<packing>"
"<property name=\"position\">5</property>"
"</packing>"
"</child>"
"</widget>"
"</child>"
"</widget>"
"<packing>"
"<property name=\"expand\">False</property>"
"<property name=\"fill\">False</property>"
"<property name=\"position\">1</property>"
"</packing>"
"</child>"
"</widget>"
"<packing>"
"<property name=\"expand\">False</property>"
"<property name=\"fill\">False</property>"
"<property name=\"position\">0</property>"
"</packing>"
"</child>"
"<child>"
"<widget class=\"GtkVBox\" id=\"vbox19\">"
"<property name=\"visible\">True</property>"
"<property name=\"spacing\">6</property>"
"<child>"
"<widget class=\"GtkLabel\" id=\"label14\">"
"<property name=\"visible\">True</property>"
"<property name=\"xalign\">0</property>"
"<property name=\"label\" translatable=\"yes\">&lt;b&gt;Font and colors&lt;/b&gt;</property>"
"<property name=\"use_markup\">True</property>"
"</widget>"
"<packing>"
"<property name=\"expand\">False</property>"
"<property name=\"fill\">False</property>"
"<property name=\"position\">0</property>"
"</packing>"
"</child>"
"<child>"
"<widget class=\"GtkAlignment\" id=\"alignment10\">"
"<property name=\"visible\">True</property>"
"<property name=\"left_padding\">12</property>"
"<child>"
"<widget class=\"GtkVBox\" id=\"vbox20\">"
"<property name=\"visible\">True</property>"
"<property name=\"spacing\">6</property>"
"<child>"
"<widget class=\"GtkTable\" id=\"table2\">"
"<property name=\"visible\">True</property>"
"<property name=\"n_rows\">2</property>"
"<property name=\"n_columns\">2</property>"
"<property name=\"column_spacing\">6</property>"
"<property name=\"row_spacing\">6</property>"
"<child>"
"<widget class=\"GtkLabel\" id=\"label99\">"
"<property name=\"visible\">True</property>"
"<property name=\"xalign\">1</property>"
"<property name=\"label\" translatable=\"yes\">Font:</property>"
"</widget>"
"<packing>"
"<property name=\"x_options\">GTK_FILL</property>"
"<property name=\"y_options\"></property>"
"</packing>"
"</child>"
"<child>"
"<widget class=\"GtkComboBox\" id=\"color_scheme_combo\">"
"<property name=\"visible\">True</property>"
"</widget>"
"<packing>"
"<property name=\"left_attach\">1</property>"
"<property name=\"right_attach\">2</property>"
"<property name=\"top_attach\">1</property>"
"<property name=\"bottom_attach\">2</property>"
"<property name=\"x_options\">GTK_FILL</property>"
"<property name=\"y_options\"></property>"
"</packing>"
"</child>"
"<child>"
"<widget class=\"GtkLabel\" id=\"label100\">"
"<property name=\"visible\">True</property>"
"<property name=\"xalign\">1</property>"
"<property name=\"label\" translatable=\"yes\">Color scheme:</property>"
"</widget>"
"<packing>"
"<property name=\"top_attach\">1</property>"
"<property name=\"bottom_attach\">2</property>"
"<property name=\"x_options\">GTK_FILL</property>"
"<property name=\"y_options\"></property>"
"</packing>"
"</child>"
"<child>"
"<widget class=\"GtkFontButton\" id=\"fontbutton:MooFontButton\">"
"<property name=\"visible\">True</property>"
"<property name=\"can_focus\">False</property>"
"<property name=\"receives_default\">False</property>"
"<property name=\"use_font\">True</property>"
"<property name=\"use_size\">True</property>"
"</widget>"
"<packing>"
"<property name=\"left_attach\">1</property>"
"<property name=\"right_attach\">2</property>"
"<property name=\"y_options\"></property>"
"</packing>"
"</child>"
"</widget>"
"<packing>"
"<property name=\"expand\">False</property>"
"<property name=\"position\">0</property>"
"</packing>"
"</child>"
"</widget>"
"</child>"
"</widget>"
"<packing>"
"<property name=\"expand\">False</property>"
"<property name=\"fill\">False</property>"
"<property name=\"position\">1</property>"
"</packing>"
"</child>"
"</widget>"
"<packing>"
"<property name=\"expand\">False</property>"
"<property name=\"fill\">False</property>"
"<property name=\"position\">1</property>"
"</packing>"
"</child>"
""
"<child>"
"<widget class=\"GtkVBox\" id=\"vbox_spell\">"
"<property name=\"visible\">True</property>"
"<property name=\"spacing\">6</property>"
"<child>"
"<widget class=\"GtkLabel\" id=\"label_spell_hdr\">"
"<property name=\"visible\">True</property>"
"<property name=\"xalign\">0</property>"
"<property name=\"label\" translatable=\"yes\">&lt;b&gt;Spell-check&lt;/b&gt;</property>"
"<property name=\"use_markup\">True</property>"
"</widget>"
"<packing>"
"<property name=\"expand\">False</property>"
"<property name=\"fill\">False</property>"
"<property name=\"position\">0</property>"
"</packing>"
"</child>"
"<child>"
"<widget class=\"GtkAlignment\" id=\"alignment_spell\">"
"<property name=\"visible\">True</property>"
"<property name=\"left_padding\">12</property>"
"<child>"
"<widget class=\"GtkVBox\" id=\"vbox_spell_body\">"
"<property name=\"visible\">True</property>"
"<property name=\"spacing\">6</property>"
"<child>"
"<widget class=\"GtkCheckButton\" id=\"spell_enabled\">"
"<property name=\"visible\">True</property>"
"<property name=\"label\" translatable=\"yes\">_Enable spell-check (English)</property>"
"<property name=\"use_underline\">True</property>"
"<property name=\"draw_indicator\">True</property>"
"</widget>"
"<packing>"
"<property name=\"expand\">False</property>"
"<property name=\"position\">0</property>"
"</packing>"
"</child>"
"<child>"
"<widget class=\"GtkLabel\" id=\"label_spell_scope\">"
"<property name=\"visible\">True</property>"
"<property name=\"xalign\">0</property>"
"<property name=\"label\" translatable=\"yes\">Check:</property>"
"</widget>"
"<packing>"
"<property name=\"expand\">False</property>"
"<property name=\"position\">1</property>"
"</packing>"
"</child>"
"<child>"
"<widget class=\"GtkAlignment\" id=\"alignment_spell_scope\">"
"<property name=\"visible\">True</property>"
"<property name=\"left_padding\">12</property>"
"<child>"
"<widget class=\"GtkVBox\" id=\"vbox_spell_scope\">"
"<property name=\"visible\">True</property>"
"<property name=\"spacing\">2</property>"
"<child>"
"<widget class=\"GtkRadioButton\" id=\"spell_scope_auto\">"
"<property name=\"visible\">True</property>"
"<property name=\"label\" translatable=\"yes\">_Auto (everything in prose, comments and strings in code)</property>"
"<property name=\"use_underline\">True</property>"
"<property name=\"draw_indicator\">True</property>"
"<property name=\"active\">True</property>"
"</widget>"
"<packing>"
"<property name=\"expand\">False</property>"
"<property name=\"position\">0</property>"
"</packing>"
"</child>"
"<child>"
"<widget class=\"GtkRadioButton\" id=\"spell_scope_all\">"
"<property name=\"visible\">True</property>"
"<property name=\"label\" translatable=\"yes\">A_ll text (always check every word)</property>"
"<property name=\"use_underline\">True</property>"
"<property name=\"draw_indicator\">True</property>"
"<property name=\"group\">spell_scope_auto</property>"
"</widget>"
"<packing>"
"<property name=\"expand\">False</property>"
"<property name=\"position\">1</property>"
"</packing>"
"</child>"
"<child>"
"<widget class=\"GtkRadioButton\" id=\"spell_scope_code\">"
"<property name=\"visible\">True</property>"
"<property name=\"label\" translatable=\"yes\">_Comments and strings only</property>"
"<property name=\"use_underline\">True</property>"
"<property name=\"draw_indicator\">True</property>"
"<property name=\"group\">spell_scope_auto</property>"
"</widget>"
"<packing>"
"<property name=\"expand\">False</property>"
"<property name=\"position\">2</property>"
"</packing>"
"</child>"
"</widget>"
"</child>"
"</widget>"
"<packing>"
"<property name=\"expand\">False</property>"
"<property name=\"position\">2</property>"
"</packing>"
"</child>"
"</widget>"
"</child>"
"</widget>"
"<packing>"
"<property name=\"expand\">False</property>"
"<property name=\"fill\">False</property>"
"<property name=\"position\">1</property>"
"</packing>"
"</child>"
"</widget>"
"<packing>"
"<property name=\"expand\">False</property>"
"<property name=\"fill\">False</property>"
"<property name=\"position\">2</property>"
"</packing>"
"</child>"
""
"</widget>"
"</child>"
"</widget>"
"</glade-interface>"

;

typedef struct PrefsGeneralXml PrefsGeneralXml;

struct PrefsGeneralXml {
    MooGladeXML *xml;

    GtkVBox *PrefsGeneral;
    GtkCheckButton *smarthome;
    GtkCheckButton *enable_auto_indent;
    GtkCheckButton *usespaces;
    GtkCheckButton *backspace_indents;
    GtkCheckButton *tab_indents;
    GtkSpinButton *indent_width;
    GtkSpinButton *tab_width;
    GtkComboBox *color_scheme_combo;
    MooFontButton *fontbutton;
    GtkVBox *vbox_spell;
    GtkLabel *label_spell_hdr;
    GtkAlignment *alignment_spell;
    GtkVBox *vbox_spell_body;
    GtkCheckButton *spell_enabled;
    GtkLabel *label_spell_scope;
    GtkAlignment *alignment_spell_scope;
    GtkVBox *vbox_spell_scope;
    GtkRadioButton *spell_scope_auto;
    GtkRadioButton *spell_scope_all;
    GtkRadioButton *spell_scope_code;

};

static void
_prefs_general_xml_free (PrefsGeneralXml *xml)
{
    if (xml)
    {
        if (xml->xml)
            g_object_unref (xml->xml);
        g_free (xml);
    }
}

G_GNUC_UNUSED static PrefsGeneralXml *
prefs_general_xml_get (gpointer widget)
{
    return (PrefsGeneralXml*) g_object_get_data (G_OBJECT (widget), "moo-generated-glade-xml");
}

static gboolean
_prefs_general_xml_finish_build (PrefsGeneralXml *xml)
{
    g_return_val_if_fail(xml != NULL, FALSE);

    xml->PrefsGeneral = (GtkVBox*) moo_glade_xml_get_widget (xml->xml, "PrefsGeneral");
    g_return_val_if_fail (xml->PrefsGeneral != NULL, FALSE);
    xml->smarthome = (GtkCheckButton*) moo_glade_xml_get_widget (xml->xml, "smarthome");
    g_return_val_if_fail (xml->smarthome != NULL, FALSE);
    xml->enable_auto_indent = (GtkCheckButton*) moo_glade_xml_get_widget (xml->xml, "enable_auto_indent");
    g_return_val_if_fail (xml->enable_auto_indent != NULL, FALSE);
    xml->usespaces = (GtkCheckButton*) moo_glade_xml_get_widget (xml->xml, "usespaces");
    g_return_val_if_fail (xml->usespaces != NULL, FALSE);
    xml->backspace_indents = (GtkCheckButton*) moo_glade_xml_get_widget (xml->xml, "backspace_indents");
    g_return_val_if_fail (xml->backspace_indents != NULL, FALSE);
    xml->tab_indents = (GtkCheckButton*) moo_glade_xml_get_widget (xml->xml, "tab_indents");
    g_return_val_if_fail (xml->tab_indents != NULL, FALSE);
    xml->indent_width = (GtkSpinButton*) moo_glade_xml_get_widget (xml->xml, "indent_width");
    g_return_val_if_fail (xml->indent_width != NULL, FALSE);
    xml->tab_width = (GtkSpinButton*) moo_glade_xml_get_widget (xml->xml, "tab_width");
    g_return_val_if_fail (xml->tab_width != NULL, FALSE);
    xml->color_scheme_combo = (GtkComboBox*) moo_glade_xml_get_widget (xml->xml, "color_scheme_combo");
    g_return_val_if_fail (xml->color_scheme_combo != NULL, FALSE);
    xml->fontbutton = (MooFontButton*) moo_glade_xml_get_widget (xml->xml, "fontbutton:MooFontButton");
    g_return_val_if_fail (xml->fontbutton != NULL, FALSE);
    xml->vbox_spell = (GtkVBox*) moo_glade_xml_get_widget (xml->xml, "vbox_spell");
    g_return_val_if_fail (xml->vbox_spell != NULL, FALSE);
    xml->label_spell_hdr = (GtkLabel*) moo_glade_xml_get_widget (xml->xml, "label_spell_hdr");
    g_return_val_if_fail (xml->label_spell_hdr != NULL, FALSE);
    xml->alignment_spell = (GtkAlignment*) moo_glade_xml_get_widget (xml->xml, "alignment_spell");
    g_return_val_if_fail (xml->alignment_spell != NULL, FALSE);
    xml->vbox_spell_body = (GtkVBox*) moo_glade_xml_get_widget (xml->xml, "vbox_spell_body");
    g_return_val_if_fail (xml->vbox_spell_body != NULL, FALSE);
    xml->spell_enabled = (GtkCheckButton*) moo_glade_xml_get_widget (xml->xml, "spell_enabled");
    g_return_val_if_fail (xml->spell_enabled != NULL, FALSE);
    xml->label_spell_scope = (GtkLabel*) moo_glade_xml_get_widget (xml->xml, "label_spell_scope");
    g_return_val_if_fail (xml->label_spell_scope != NULL, FALSE);
    xml->alignment_spell_scope = (GtkAlignment*) moo_glade_xml_get_widget (xml->xml, "alignment_spell_scope");
    g_return_val_if_fail (xml->alignment_spell_scope != NULL, FALSE);
    xml->vbox_spell_scope = (GtkVBox*) moo_glade_xml_get_widget (xml->xml, "vbox_spell_scope");
    g_return_val_if_fail (xml->vbox_spell_scope != NULL, FALSE);
    xml->spell_scope_auto = (GtkRadioButton*) moo_glade_xml_get_widget (xml->xml, "spell_scope_auto");
    g_return_val_if_fail (xml->spell_scope_auto != NULL, FALSE);
    xml->spell_scope_all = (GtkRadioButton*) moo_glade_xml_get_widget (xml->xml, "spell_scope_all");
    g_return_val_if_fail (xml->spell_scope_all != NULL, FALSE);
    xml->spell_scope_code = (GtkRadioButton*) moo_glade_xml_get_widget (xml->xml, "spell_scope_code");
    g_return_val_if_fail (xml->spell_scope_code != NULL, FALSE);

    g_object_set_data_full (G_OBJECT (xml->PrefsGeneral), "moo-generated-glade-xml",
                            xml, (GDestroyNotify) _prefs_general_xml_free);
    return TRUE;
}

static gboolean
prefs_general_xml_build (PrefsGeneralXml *xml)
{
    GError *error = NULL;
    if (!moo_glade_xml_parse_memory (xml->xml, _prefs_general_xml_glade_xml, -1, "PrefsGeneral", &error))
    {
        g_critical ("Could not parse glade xml: %s", error->message);
        g_error_free (error);
        return FALSE;
    }
    return _prefs_general_xml_finish_build (xml);
}

static gboolean
prefs_general_xml_fill (PrefsGeneralXml *xml, GtkWidget *root)
{
    GError *error = NULL;
    if (!moo_glade_xml_fill_widget (xml->xml, root, _prefs_general_xml_glade_xml, -1, "PrefsGeneral", &error))
    {
        g_critical ("Could not parse glade xml: %s", error->message);
        g_error_free (error);
        return FALSE;
    }
    return _prefs_general_xml_finish_build (xml);
}

static PrefsGeneralXml *
prefs_general_xml_new_empty (void)
{
    PrefsGeneralXml *xml = g_new0 (PrefsGeneralXml, 1);
    xml->xml = moo_glade_xml_new_empty (GETTEXT_PACKAGE);

    return xml;
}

G_GNUC_UNUSED static PrefsGeneralXml *
prefs_general_xml_new (void)
{
    PrefsGeneralXml *xml = prefs_general_xml_new_empty ();
    if (!prefs_general_xml_build (xml))
    {
        _prefs_general_xml_free (xml);
        xml = NULL;
    }
    return xml;
}

G_GNUC_UNUSED static PrefsGeneralXml *
prefs_general_xml_new_with_root (GtkWidget *root)
{
    PrefsGeneralXml *xml = prefs_general_xml_new_empty ();
    if (!prefs_general_xml_fill (xml, root))
    {
        _prefs_general_xml_free (xml);
        xml = NULL;
    }
    return xml;
}
