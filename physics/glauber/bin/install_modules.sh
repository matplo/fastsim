#!/bin/bash

XDIR="/Users/ploskon/devel/sandbox/physics/glauber"

$XDIR/bin/make_module.sh
mkdir -p $HOME/privatemodules/
cp -vr $XDIR/modules/* $HOME/privatemodules/

