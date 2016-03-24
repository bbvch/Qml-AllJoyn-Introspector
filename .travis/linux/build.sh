#!/bin/sh

set -e

mkdir /build
mkdir /dist
cd /build
qmake /source
make -j2
make -j2 install INSTALL_ROOT=/dist

# run tests
test/test
