#!/bin/bash

gitrepo="http://root.cern.ch/git/root.git"
ROOT_VER="$1"

if [ -z "$ROOT_VER" ]; then
    echo "[e] $ROOT_VER not set - 1st argument"
    exit
fi

cdir=$PWD

wdir="$PWD/root.git"
echo "[i] cloning git"
git clone $gitrepo $wdir
cd $wdir
echo "[i] git remote prune origin"
git remote prune origin
echo "[i] git checkout $ROOT_VER"
#git checkout $([ "$ROOT_VER" == 'trunk' ] && echo master || echo "$ROOT_VER")
git checkout $ROOT_VER
#git pull
echo "[i] git pull $gitrepo $ROOT_VER"
git pull $gitrepo $ROOT_VER

if [ -z "$ROOTSYS" ]; then
    echo "[e] ROOTSYS is not set. Stop here."
else
    ./configure \
	--prefix=$ROOTSYS \
	--enable-mathmore \
	--enable-minuit2 \
	--enable-roofit \
	--enable-soversion
fi

time make -j 4 && make install

cd $cdir
