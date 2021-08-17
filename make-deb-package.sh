#!/bin/sh

cmake .
make
cp scalculator2 pkg-debian/usr/bin
dpkg -b pkg-debian/ scalculator_amd64.deb
