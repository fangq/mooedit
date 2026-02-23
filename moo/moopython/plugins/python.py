import gi
from gi.repository import GObject, Pango
import os
import moo
from moo import _

try:
    import pyconsole
    have_pyconsole = True
except ImportError:
    have_pyconsole = False

PLUGIN_ID = "Python"

class Plugin(moo.Plugin):
    def do_init(self):
        editor = moo.Editor.instance()
        xml = editor.get_ui_xml()
        if xml is None:
            return False
        self.ui_merge_id = xml.new_merge_id()
        if have_pyconsole:
            moo.window_class_add_action(moo.EditWindow, "PythonConsole",
                                        display_name=_("Python Console"),
                                        label=_("Python Console"),
                                        callback=self.show_console)
            xml.add_item(self.ui_merge_id, "ToolsMenu",
                         "PythonConsole", "PythonConsole", -1)
        moo.window_class_add_action(moo.EditWindow, "RunFile",
                                    display_name=_("Run File"),
                                    label=_("Run File"),
                                    stock_id=moo.STOCK_EXECUTE,
                                    default_accel="<shift>F9",
                                    callback=self.run_file)
        moo.edit_window_set_action_filter("RunFile", moo.ACTION_CHECK_SENSITIVE, "langs:python")
        xml.add_item(self.ui_merge_id, "ToolsMenu",
                     "RunFile", "RunFile", -1)
        return True

    def do_deinit(self):
        editor = moo.Editor.instance()
        xml = editor.get_ui_xml()
        xml.remove_ui(self.ui_merge_id)
        moo.window_class_remove_action(moo.EditWindow, "PythonConsole")
        moo.window_class_remove_action(moo.EditWindow, "RunFile")

    def show_console(self, window):
        # Import Gtk only when needed
        try:
            gi.require_version('Gtk', '2.0')
        except Exception:
            pass
        from gi.repository import Gtk
        win = Gtk.Window()
        swin = Gtk.ScrolledWindow()
        swin.set_policy(Gtk.PolicyType.AUTOMATIC, Gtk.PolicyType.ALWAYS)
        win.add(swin)
        dic = {'editor': moo.Editor.instance(),
               'window': moo.Editor.instance().get_active_window(),
               'doc': moo.Editor.instance().get_active_doc()}
        console_type = pyconsole.ConsoleType(moo.TextView)
        console = console_type(use_rlcompleter=False,
                               start_script="import moo\n", locals=dic)
        console.set_property("highlight-current-line", False)
        console.modify_font(Pango.FontDescription("Monospace"))
        swin.add(console)
        win.set_default_size(400, 300)
        win.set_title("Python Console")
        win.show_all()

    def run_file(self, window):
        import medit.runpython
        filename = os.environ.get('PYTHON_MASTER_FILE')
        if filename is None:
            doc = window.get_active_doc()
            if not doc:
                return
            if not doc.get_filename() or doc.get_status() & moo.EDIT_STATUS_MODIFIED:
                if not doc.save():
                    return
            filename = doc.get_filename()
        r = medit.runpython.Runner(window)
        r.run(filename)

GObject.type_register(Plugin)
__plugin__ = Plugin
