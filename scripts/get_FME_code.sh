#!/bin/bash

savedir=$PWD

if [ -d $FASTSIM ]; then
	cd $FASTSIM
	[ "clean" == "$1" ] && rm -rf ./AliGenFME
	git clone https://github.com/xcheung/AliGenFME
fi

cd $savedir
