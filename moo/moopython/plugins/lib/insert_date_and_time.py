import time

try:
    import moo
    moo.prefs_new_key_string('Tools/InsertDateAndTime', '%c')
except:
    pass

formats = [
    ("%c",                    "Locale default"),
    ("%Y-%m-%d %H:%M:%S",    "2024-01-15 14:30:00"),
    ("%Y-%m-%d",              "2024-01-15"),
    ("%d/%m/%Y",              "15/01/2024"),
    ("%d/%m/%y",              "15/01/24"),
    ("%B %d, %Y",             "January 15, 2024"),
    ("%A %B %d %Y",           "Monday January 15 2024"),
    ("%H:%M:%S",              "14:30:00"),
    ("%H:%M",                 "14:30"),
    ("%I:%M %p",              "02:30 PM"),
    ("%x",                    "Locale date"),
    ("%X",                    "Locale time"),
    ("%x %X",                 "Locale date+time"),
    ("%d/%m/%Y %H:%M:%S",    "15/01/2024 14:30:00"),
]

def get_format(parent=None):
    """Get date format. Since GTK 2 dialogs don't work with PyGObject 3,
    use the saved preference or default format."""
    try:
        fmt = moo.prefs_get_string('Tools/InsertDateAndTime')
        if fmt:
            return fmt
    except:
        pass
    return '%c'
