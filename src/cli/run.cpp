// Copyright (C) 2019 Luxoft Sweden AB
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "cli/run.h"

#include <glib-unix.h>
#include <glibmm.h>

#include <csignal>
#include <iostream>

namespace TemplateDBusService::Cli
{
    namespace
    {
        using TemplateProxy = com::luxoft::TemplateProxy;

        gboolean sigint_callback(void *main_loop)
        {
            static_cast<Glib::MainLoop *>(main_loop)->quit();
            return G_SOURCE_CONTINUE;
        }

        bool monitor_until_ctrl_c(const Glib::RefPtr<TemplateProxy> &template_proxy)
        {
            Glib::RefPtr<Glib::MainLoop> main_loop = Glib::MainLoop::create();
            guint sigint_source_id = g_unix_signal_add(SIGINT, sigint_callback, main_loop.get());

            std::cout << "Monitoring, press Ctrl-C to quit.\n";

            template_proxy->RemoveMeBar_signal.connect([](guint32 something) {
                std::cout << "RemoveMeBar(something=" << something << ")\n";
            });

            template_proxy->RemoveMeBaz_changed().connect(
                [&] { std::cout << "RemoveMeBaz=" << template_proxy->RemoveMeBaz_get() << '\n'; });

            main_loop->run();

            g_source_remove(sigint_source_id);

            return true;
        }

        // FIXME
    }

    int run(const Glib::RefPtr<TemplateProxy> &template_proxy, const Arguments &arguments)
    {
        // FIXME
        std::cout << "Service method returned: " << template_proxy->RemoveMeFoo_sync(123) << '\n';

        if (arguments.monitor) {
            if (!monitor_until_ctrl_c(template_proxy)) {
                return EXIT_FAILURE;
            }
        }

        return EXIT_SUCCESS;
    }
}
