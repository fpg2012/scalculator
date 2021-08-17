#!/bin/sh

mkdir build
cd build
cmake ..
make
mkdir -p pkg-debian/DEBIAN
mkdir -p pkg-debian/usr/bin
echo """Package: scalculator
Version: 1.0.0
Architecture: amd64
Essential: no
Section: utils
Priority: optional
Depends: libqt5gui5, libsevaluator
Maintainer: nth233<fpg2012@yeah.net>
Installed-Size: 1
Description: simple calculator with big number support.""" > pkg-debian/DEBIAN/control
cp scalculator2 pkg-debian/usr/bin/
dpkg -b pkg-debian/ scalculator_amd64.deb
