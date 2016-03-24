#!/bin/bash

savedir=$PWD

if [ -d $FASTSIM ]; then
	cd $FASTSIM
	[ "clean" == "$1" ] && rm -rfv ./EmcalTriggerFast
	#git clone https://github.com/mfasDa/EmcalTriggerFast
	git clone https://github.com/matplo/EmcalTriggerFast
fi

cd $savedir
