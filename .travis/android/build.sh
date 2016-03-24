#!/bin/sh

set -e

mkdir /build
mkdir /dist
cd /build
qmake /source
make -j2 install INSTALL_ROOT=/dist
androiddeployqt --input /build/application/android-libAllJoyn-Introspector.so-deployment-settings.json --output /dist --deployment bundled --gradle --release
