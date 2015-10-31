#!/bin/bash

for fn in cmake_install.cmake CMakeCache.txt Makefile CMakeFiles *_Dict.* \
	lib* install_manifest.txt
do
	rm -rfv $fn
done
