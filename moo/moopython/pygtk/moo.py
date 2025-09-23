#
#  moo-mod.py
#
#  Copyright (C) 2004-2010 by Yevgen Muntyan <emuntyan@users.sourceforge.net>
#
#  This file is part of medit.  medit is free software; you can
#  redistribute it and/or modify it under the terms of the
#  GNU Lesser General Public License as published by the
#  Free Software Foundation; either version 2.1 of the License,
#  or (at your option) any later version.
#
#  You should have received a copy of the GNU Lesser General Public
#  License along with medit.  If not, see <http://www.gnu.org/licenses/>.
#

""" moo module """

# Python 3 + PyGObject imports
import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk as _gtk
from gi.repository import GObject as _gobject

# Import the native _moo module (assuming it's been updated for Python 3)
import _moo
from _moo import *

# note, these aren't standard gettext functions
_ = gettext
D_ = dgettext

def N_(string):
    return string

class _PluginWontLoad(Exception):
    def __repr__(self):
        return 'PluginWontLoad'

def _cancel_plugin_loading():
    raise _PluginWontLoad()

class _ActionFactory(object):
    def __init__(self, action_id, **kwargs):
        object.__init__(self)
        self.id = action_id

        self.props = {}
        self.fake_props = {}

        # Python 3: dict.keys() returns a view, convert to list for compatibility
        for key in list(kwargs.keys()):
            if key in ["callback"]:
                self.fake_props[key] = kwargs[key]
            elif kwargs[key] is not None or key not in ["stock_id"]:
                self.props[key] = kwargs[key]

    def __call__(self, window):
        self.window = window
        # PyGObject: Use GObject.new() instead of _gobject.new()
        action = _gobject.new(Action, name=self.id, **self.props)
        self.set_fake_props(action)
        return action

    def set_fake_props(self, action):
        def _activate(action, callback, window):
            callback(window)

        # Python 3: dict.keys() returns a view, convert to list
        for key in list(self.fake_props.keys()):
            if key == "callback":
                action.connect("activate", _activate, self.fake_props[key], self.window)
            else:
                raise ValueError("unknown property " + key)

    def set_props(self, action):
        # Python 3: dict.keys() returns a view, convert to list
        for key in list(self.props.keys()):
            action.set_property(key, self.props[key])

def window_class_add_action(klass, action_id, group=None, **kwargs):
    if "factory" in kwargs:
        _moo.window_class_add_action(klass, action_id, group, kwargs["factory"])
    else:
        _moo.window_class_add_action(klass, action_id, group, _ActionFactory(action_id, **kwargs))