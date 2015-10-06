#!/bin/bash

for fn in cmake_install.cmake CMakeCache.txt Makefile CMakeFiles libtoymcpy8Util.dylib toymcpy8 install_manifest.txt ./build
do
	rm -rfv $fn
done
