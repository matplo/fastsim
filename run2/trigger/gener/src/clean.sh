#!/bin/bash

for fn in cmake_install.cmake CMakeCache.txt Makefile CMakeFiles libtoymcpy8Util.dylib toymcpy8
do
	rm -rfv $fn
done
