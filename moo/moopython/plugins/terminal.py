# Terminal plugin requires VTE which needs GTK 3.
# medit is currently built against GTK 2, so VTE cannot load.
# This plugin will become functional after medit is migrated to GTK 3.
import sys
import moo
print("Terminal plugin: requires GTK 3 (medit uses GTK 2) — disabled", file=sys.stderr)
moo._cancel_plugin_loading()
