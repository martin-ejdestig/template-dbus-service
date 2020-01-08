Template D-Bus service
======================

Template for creating a D-Bus service component.

Dependencies
============

- [gdbus-codegen-glibmm](https://github.com/Pelagicore/gdbus-codegen-glibmm)
- glibmm (2.56)
- googletest (1.8.1, for tests, optional)

Building
========

[Meson](https://mesonbuild.com/) is used for building. To build simply run:

```shell
meson build
ninja -C build
```

Installing and Running
======================

After building, installation can be performed by running:

```shell
sudo ninja -C build install
```

By default this will install under `/usr/local`. To change this pass `--prefix` when invoking
`meson` or `meson configure`, e.g. `meson build --prefix=/usr`.

`systemctl daemon-reload` must be run for systemd to notice the newly installed service file. The
service will now start when a D-Bus call is made to it on the system bus. It can also be started
manually by running `systemctl start template-dbus-service`.

It is possible to run the daemon directly from the build directory and on the session bus, which
might facilitate testing and debugging during development. To do this run:

```shell
export DBUS_SYSTEM_BUS_ADDRESS=$DBUS_SESSION_BUS_ADDRESS
```

And then run the built daemon executable directly from the build directory.

Running Tests
=============

Tests can be run with:

```shell
meson test -C build
```

"No tests defined." is printed if the required version of googletest could not be found.

Code Checking
=============

[Clang-Format](https://clang.llvm.org/docs/ClangFormat.html) and
[Clang-Tidy](https://clang.llvm.org/extra/clang-tidy/) are used for code style checking and
"linting". Clang's [static analyzer](https://clang-analyzer.llvm.org/) checks are run as part of
[Clang-Tidy](https://clang.llvm.org/extra/clang-tidy/) as well. A [script](tools/check) exists to
simplify running these tools. After building, simply run:

```shell
tools/check . build
```

Note that different versions of `clang-format` and `clang-tidy` may give different results. See
[tools/ci/Dockerfile](tools/ci/Dockerfile) for what versions are run in the
[CI system](tools/ci).

The [CI system](tools/ci) also makes sure that the code compiles without any warnings. To turn
warnings into errors when building locally, pass `-Dwerror=true` when invoking `meson` or
`meson configure`.

License and Copyright
=====================

Copyright © 2019 Luxoft Sweden AB

The source code in this repository is subject to the terms of the MPL-2.0 license, please see
included "LICENSE" file for details. License information for any other files is either explicitly
stated or defaults to the MPL-2.0 license.
