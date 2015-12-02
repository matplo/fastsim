#!/bin/bash

XDIR="<dir to be set>"

$XDIR/bin/make_module.sh
mkdir -p $HOME/privatemodules/
cp -vr $XDIR/modules/* $HOME/privatemodules/

