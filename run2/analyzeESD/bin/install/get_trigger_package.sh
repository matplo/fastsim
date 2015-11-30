#!/bin/bash

savedir=$PWD

if [ -d $RUN2AESDDIR ]; then
	cd $RUN2AESDDIR
	[ "clean" == "$1" ] && rm -rfv ./EmcalTriggerFast
	#git clone https://github.com/mfasDa/EmcalTriggerFast
	git clone https://github.com/matplo/EmcalTriggerFast
fi

cd $savedir
