/* eggsmclient-osx.c
 *
 * No-op session management backend for macOS (GDK Quartz).
 * macOS does not have an XSMP session manager; we provide the symbols
 * required by eggsmclient.c when GDK_WINDOWING_QUARTZ is defined so
 * that the build links cleanly.  Graceful shutdown (Cmd-Q / logout) is
 * handled by the normal GtkApplication / GDK Quartz event loop.
 *
 * Copyright (C) 2007 Novell, Inc.
 * Copyright (C) 2024 medit contributors
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 */

#include "config.h"
#include "eggsmclient-private.h"

#define EGG_TYPE_SM_CLIENT_OSX            (egg_sm_client_osx_get_type ())
#define EGG_SM_CLIENT_OSX(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), EGG_TYPE_SM_CLIENT_OSX, EggSMClientOSX))
#define EGG_SM_CLIENT_OSX_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST    ((klass), EGG_TYPE_SM_CLIENT_OSX, EggSMClientOSXClass))
#define EGG_IS_SM_CLIENT_OSX(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EGG_TYPE_SM_CLIENT_OSX))
#define EGG_IS_SM_CLIENT_OSX_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE    ((klass), EGG_TYPE_SM_CLIENT_OSX))

typedef EggSMClient      EggSMClientOSX;
typedef EggSMClientClass EggSMClientOSXClass;

G_DEFINE_TYPE (EggSMClientOSX, egg_sm_client_osx, EGG_TYPE_SM_CLIENT)

static void
egg_sm_client_osx_init (G_GNUC_UNUSED EggSMClientOSX *client)
{
}

static void
sm_client_osx_startup (G_GNUC_UNUSED EggSMClient *client,
                       G_GNUC_UNUSED const char   *client_id)
{
}

static void
egg_sm_client_osx_class_init (EggSMClientOSXClass *klass)
{
    klass->startup = sm_client_osx_startup;
}

EggSMClient *
egg_sm_client_osx_new (void)
{
    return g_object_new (EGG_TYPE_SM_CLIENT_OSX, NULL);
}
