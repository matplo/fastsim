#!/bin/bash

savedir=$PWD

if [ -d $RUN2EMCTRIGGER ]; then
	cd $RUN2EMCTRIGGER
	[ "clean" == "$1" ] && rm -rf ./AliGenFME
	git clone https://github.com/xcheung/AliGenFME
fi

cd $savedir
