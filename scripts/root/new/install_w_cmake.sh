#!/bin/bash

savedir=$PWD

# from https://root.cern.ch/get-root-sources
# https://root.cern.ch/building-root

wdir=$HOME/software/rootgit

mkdir $wdir
cd $wdir

git clone http://root.cern.ch/git/root.git

#version=v6-05-02
version=v5-34-32
tdir=$HOME/software/root/$version

cd root
git tag -l
git checkout -b $version $version

cd $wdir

dname=`date +"%Y-%m-%d"`
bdir="build_$version_$dname"
rm -rf $bdir
mkdir $bdir
cd $bdir

cmake $wdir/root
cmake --build .
cmake -DCMAKE_INSTALL_PREFIX=$tdir -P cmake_install.cmake

ln -s $tdir/bin/thisroot.sh "/usr/local/bin/root-$version"

cd $savedir


