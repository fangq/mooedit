# Terminal plugin requires VTE which needs GTK 3.
# medit is now built against GTK 3.
# TODO: Re-enable VTE terminal support.
import sys
import moo
# Terminal plugin: TODO re-enable VTE support
moo._cancel_plugin_loading()
