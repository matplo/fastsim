#!/bin/bash

gitrepo="http://root.cern.ch/git/root.git"
ROOT_VER="$1"

if [ -z "$ROOT_VER" ]; then
    echo "[e] $ROOT_VER not set - 1st argument"
    exit
fi

if [ -z "$ALICE_PREFIX" ]; then
    echo "[e] ALICE_PREFIX is not set"
    exit
else
    echo "[i] ALICE_PREFIX = $ALICE_PREFIX"
fi

mkdir -p "$ALICE_PREFIX/root/git"
cd "$ALICE_PREFIX/root/git"
echo "[i] cloning git"
git clone $gitrepo .
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
    rsync -avc --exclude '**/.git' "$ALICE_PREFIX/root/git/" "$ROOTSYS"
    cd "$ROOTSYS"
    
    echo "At this point you should have env also for alien..."

    ./configure \
	--with-pythia6-uscore=SINGLE \
	--with-alien-incdir=$GSHELL_ROOT/include \
	--with-alien-libdir=$GSHELL_ROOT/lib \
	--with-monalisa-incdir="$GSHELL_ROOT/include" \
	--with-monalisa-libdir="$GSHELL_ROOT/lib" \
	--with-xrootd=$GSHELL_ROOT \
	--with-f77=/usr/local/bin/gfortran \
	--with-clang \
	--enable-minuit2 \
	--enable-roofit \
	--enable-soversion \
	--disable-bonjour \
	--enable-builtin-freetype \
	--disable-fink
fi
