""" moo module """
from gi.repository import GObject as _gobject

import _moo
from _moo import *

try:
    _ = gettext
except NameError:
    _ = lambda s: s

try:
    D_ = dgettext
except NameError:
    D_ = lambda s: s

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
        for key in list(kwargs.keys()):
            if key in ["callback"]:
                self.fake_props[key] = kwargs[key]
            elif kwargs[key] is not None or key not in ["stock_id"]:
                self.props[key] = kwargs[key]

    def __call__(self, window):
        self.window = window
        action = _gobject.new(Action, name=self.id, **self.props)
        self.set_fake_props(action)
        return action

    def set_fake_props(self, action):
        def _activate(action, callback, window):
            callback(window)
        for key in list(self.fake_props.keys()):
            if key == "callback":
                action.connect("activate", _activate, self.fake_props[key], self.window)
            else:
                raise ValueError("unknown property " + key)

    def set_props(self, action):
        for key in list(self.props.keys()):
            action.set_property(key, self.props[key])

def window_class_add_action(klass, action_id, group=None, **kwargs):
    if "factory" in kwargs:
        _moo.window_class_add_action(klass, action_id, group, kwargs["factory"])
    else:
        _moo.window_class_add_action(klass, action_id, group, _ActionFactory(action_id, **kwargs))
