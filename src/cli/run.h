// Copyright (C) 2019 Luxoft Sweden AB
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#ifndef TEMPLATE_DBUS_SERVICE_CLI_RUN_H
#define TEMPLATE_DBUS_SERVICE_CLI_RUN_H

#include <glibmm.h>

#include "cli/arguments.h"
#include "generated/dbus/template_proxy.h"

namespace TemplateDBusService::Cli
{
    int run(const Glib::RefPtr<com::luxoft::TemplateProxy> &template_proxy,
            const Arguments &arguments);
}

#endif // TEMPLATE_DBUS_SERVICE_CLI_RUN_H
