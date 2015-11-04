#!/bin/bash

savedir=$PWD

if [ -d $RUN2EMCTRIGGER ]; then
	cd $RUN2EMCTRIGGER
	echo "[i] updating AliGenFME"
	[ "clean" == "$1" ] && rm -rfv ./AliGenFME
	git clone https://github.com/xcheung/AliGenFME

	cd $RUN2EMCTRIGGER
	echo "[i] updating EmcalTriggerFast"
	[ "clean" == "$1" ] && rm -rfv ./EmcalTriggerFast
	#git clone https://github.com/mfasDa/EmcalTriggerFast
	git clone https://github.com/matplo/EmcalTriggerFast

	cd $RUN2EMCTRIGGER
	echo "[i] updating $RUN2EMCTRIGGER"
	git pull
fi

cd $savedir
