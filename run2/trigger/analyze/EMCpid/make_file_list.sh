#!/bin/bash

rm filelist.txt
#find . -name "EMCalTree.root" | tee filelist.txt
find . -name "root_archive.zip" -exec echo {}\#EMCalTree.root \; | tee -a filelist.txt
