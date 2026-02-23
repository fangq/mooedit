import os
import sys
import moo
from moo import _
from moo import D_

# Suppress the Gtk 2.0 override error by importing without overrides
import gi
gi.require_version('Vte', '2.91')

# Import GI modules — avoid Gtk overrides that break with GTK 2
from gi.repository import GObject, GLib, Pango, Gdk, Vte

# For Gtk, we need to work around broken overrides with GTK 2.0
# Import the raw module without triggering overrides
try:
    gi.require_version('Gtk', '2.0')
    import importlib
    _gtk_mod = importlib.import_module('gi.repository.Gtk')
    Gtk = _gtk_mod
except Exception:
    try:
        gi.require_version('Gtk', '3.0')
        from gi.repository import Gtk
    except Exception:
        moo._cancel_plugin_loading()

TERMINAL_PLUGIN_ID = "Terminal"
COLOR_SCHEME_KEY = 'Plugins/Terminal/color_scheme'
SHELL_KEY = 'Plugins/Terminal/shell'
FONT_KEY = 'Plugins/Terminal/font'
moo.prefs_new_key_string(COLOR_SCHEME_KEY, 'Default')
moo.prefs_new_key_string(SHELL_KEY, None)
moo.prefs_new_key_string(FONT_KEY, None)

def shell_supports_pushd(shell):
    name = os.path.split(shell)[1]
    return name in ["bash"]

class Terminal(Vte.Terminal):
    def __init__(self):
        Vte.Terminal.__init__(self)
        cs_name = moo.prefs_get_string(COLOR_SCHEME_KEY)
        cs = find_color_scheme(cs_name)
        self.set_color_scheme(cs)
        font_name = moo.prefs_get_string(FONT_KEY)
        if font_name:
            self.set_font(Pango.FontDescription(font_name))
        self._support_pushd = False

    def set_support_pushd(self, status):
        self._support_pushd = status

    def set_color_scheme(self, cs):
        self.__cs = cs
        if cs:
            cs.set_on_terminal(self)

    def color_scheme_item_activated(self, item, color_scheme):
        self.set_color_scheme(color_scheme)
        if color_scheme.colors:
            moo.prefs_set_string(COLOR_SCHEME_KEY, color_scheme.name)
        else:
            moo.prefs_set_string(COLOR_SCHEME_KEY, None)

    def font_item_activated(self, *whatever):
        dlg = Gtk.FontSelectionDialog("Pick a Font")
        old_font = self.get_font()
        if old_font:
            dlg.set_font_name(old_font.to_string())
        if dlg.run() == Gtk.ResponseType.OK:
            font_name = dlg.get_font_name()
            if font_name:
                new_font = Pango.FontDescription(font_name)
                if old_font is None or not old_font.equal(new_font):
                    self.set_font(new_font)
                    moo.prefs_set_string(FONT_KEY, font_name)
        dlg.destroy()

    def fill_settings_menu(self, menu):
        item = Gtk.MenuItem(label=_("Select Font"))
        item.connect('activate', self.font_item_activated)
        menu.append(item)
        item = Gtk.MenuItem(label=_("Color Scheme"))
        submenu = Gtk.Menu()
        item.set_submenu(submenu)
        group = None
        for cs in color_schemes:
            child = Gtk.RadioMenuItem(group=group, label=cs.name)
            group = child
            submenu.append(child)
            if self.__cs == cs:
                child.set_active(True)
            child.connect('activate', self.color_scheme_item_activated, cs)
        menu.append(item)

    def popup_menu(self, event=None):
        menu = Gtk.Menu()
        item = Gtk.MenuItem(label=_("Copy"))
        item.connect('activate', lambda *w: self.copy_clipboard())
        item.set_sensitive(self.get_has_selection())
        menu.append(item)
        item = Gtk.MenuItem(label=_("Paste"))
        item.connect('activate', lambda *w: self.paste_clipboard())
        menu.append(item)
        item = Gtk.MenuItem(label=_("cd to current file directory"))
        item.connect('activate', lambda *w: self.goto_file_dir(False))
        menu.append(item)
        if self._support_pushd:
            item = Gtk.MenuItem(label=_("pushd to current file directory"))
            item.connect('activate', lambda *w: self.goto_file_dir(True))
            menu.append(item)
        menu.append(Gtk.SeparatorMenuItem())
        item = Gtk.MenuItem(label=_("Settings"))
        submenu = Gtk.Menu()
        item.set_submenu(submenu)
        menu.append(item)
        self.fill_settings_menu(submenu)
        menu.show_all()
        if event is not None:
            menu.popup(None, None, None, None, event.button, event.time)
        else:
            menu.popup(None, None, None, None, 0, 0)

    def goto_file_dir(self, pushd=False):
        ed = moo.Editor.instance()
        doc = ed.get_active_doc()
        if doc is None:
            return
        path = doc.get_filename()
        if path is None:
            return
        path = os.path.split(path)[0]
        command = "pushd" if pushd else "cd"
        command += " '" + path + "'\n"
        self.feed_child(command.encode('utf-8'))

    def do_button_press_event(self, event):
        if event.button != 3 or event.type != Gdk.EventType.BUTTON_PRESS:
            return Vte.Terminal.do_button_press_event(self, event)
        self.grab_focus()
        self.popup_menu(event)
        return True

    def do_popup_menu(self):
        self.popup_menu()
        return True

class Plugin(moo.Plugin):
    def do_init(self):
        editor = moo.Editor.instance()
        xml = editor.get_ui_xml()
        if xml is None:
            return False
        self.set_win_plugin_type(WinPlugin)
        return True
    def do_deinit(self):
        pass

class WinPlugin(moo.WinPlugin):
    def start(self, *whatever):
        self.terminal.reset(True, True)
        shell = moo.prefs_get_string(SHELL_KEY)
        if not shell:
            try:
                import pwd
                shell = pwd.getpwuid(os.getuid())[6]
            except Exception:
                shell = "/bin/sh"
        self.terminal.set_support_pushd(shell_supports_pushd(shell))
        try:
            self.terminal.spawn_async(
                Vte.PtyFlags.DEFAULT, None, [shell], None,
                GLib.SpawnFlags.DEFAULT, None, None, -1, None, None)
        except (AttributeError, TypeError):
            try:
                self.terminal.spawn_sync(
                    Vte.PtyFlags.DEFAULT, None, [shell], None,
                    GLib.SpawnFlags.DEFAULT, None, None, None)
            except Exception as e:
                print("Failed to spawn shell:", e)

    def do_create(self):
        label = moo.PaneLabel(icon_name=moo.STOCK_TERMINAL,
                              label_text=_("Terminal"))
        self.terminal = Terminal()
        self.terminal.set_scrollback_lines(1000000)
        self.terminal.connect("child-exited", self._on_child_exited)
        self.start()
        frame = Gtk.Frame()
        hbox = Gtk.HBox()
        frame.add(hbox)
        hbox.pack_start(self.terminal, True, True, 0)
        scrollbar = Gtk.VScrollbar(adjustment=self.terminal.get_vadjustment())
        hbox.pack_start(scrollbar, False, False, 0)
        frame.show_all()
        self.terminal.set_size(self.terminal.get_column_count(), 10)
        self.terminal.set_size_request(10, 10)
        self.pane = self.get_window().add_pane(TERMINAL_PLUGIN_ID, frame, label, moo.PANE_POS_BOTTOM)
        self.icon_title_changed_cb_id = self.terminal.connect('icon-title-changed', self.terminal_icon_title_changed)
        self.terminal_icon_title_changed()
        return True

    def _on_child_exited(self, terminal, status):
        self.start()

    def do_destroy(self):
        self.terminal.disconnect(self.icon_title_changed_cb_id)
        self.get_window().remove_pane(TERMINAL_PLUGIN_ID)

    def terminal_icon_title_changed(self, *whatever):
        title = self.terminal.get_icon_title()
        if title:
            self.pane.set_frame_text(title)

def _parse_color(s):
    c = Gdk.RGBA()
    c.parse(s)
    return c

class ColorScheme(object):
    def __init__(self, name, colors):
        self.name = name
        self.colors = [_parse_color(c) for c in colors] if colors else None
    def set_on_terminal(self, term):
        if self.colors:
            term.set_colors(self.colors[0], self.colors[1],
                           self.colors[2:10] + self.colors[12:20])

color_schemes = [ColorScheme(n, c) for n, c in [
    [_("Default"), None],
    [_("Black on White"),
        ['#000000','#ffffff','#000000','#b21818','#18b218','#b26818','#1818b2','#b218b2','#18b2b2','#b2b2b2',
         '#000000','#ffffff','#686868','#ff5454','#54ff54','#ffff54','#5454ff','#ff54ff','#54ffff','#ffffff']],
    [_("White on Black"),
        ['#ffffff','#000000','#000000','#b21818','#18b218','#b26818','#1818b2','#b218b2','#18b2b2','#b2b2b2',
         '#ffffff','#000000','#686868','#ff5454','#54ff54','#ffff54','#5454ff','#ff54ff','#54ffff','#ffffff']],
    [_("Green on Black"),
        ['#18f018','#000000','#000000','#b21818','#18b218','#b26818','#1818b2','#b218b2','#18b2b2','#b2b2b2',
         '#18f018','#000000','#686868','#ff5454','#54ff54','#ffff54','#5454ff','#ff54ff','#54ffff','#ffffff']],
    [_("Linux Colors"),
        ['#b2b2b2','#000000','#000000','#b21818','#18b218','#b26818','#1818b2','#b218b2','#18b2b2','#b2b2b2',
         '#ffffff','#686868','#686868','#ff5454','#54ff54','#ffff54','#5454ff','#ff54ff','#54ffff','#ffffff']],
]]

def find_color_scheme(name):
    for cs in color_schemes:
        if cs.name == name:
            return cs

GObject.type_register(Terminal)
GObject.type_register(Plugin)
GObject.type_register(WinPlugin)
__plugin__ = Plugin
