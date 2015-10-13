#!/bin/bash

savedir=$PWD
if [ -z $RUN2EMCTRIGGER ]; then
	exit
fi

if [ -d $RUN2EMCTRIGGER ]; then
	cd $RUN2EMCTRIGGER

	for d in EmcalTriggerFast include lib AliGenFME .build
	do
		echo "cleaning $RUN2EMCTRIGGER/$d ..."
		rm -rf $RUN2EMCTRIGGER/$d
	done
	
	for ex in toymcpy8 testETF channelmaptester 
	do
		rm -rfv $RUN2EMCTRIGGER/bin/$ex
	done
	#rm -rfv /usr/local/lib/libEMCALTriggerFast.* /usr/local/include/TriggerBitConfig.h /usr/local/include/TriggerSetup.h /usr/local/include/TriggerMappingEmcalSimple.h /usr/local/include/TriggerChannelMap.h /usr/local/include/TriggerAlgorithm.h /usr/local/include/JetTriggerAlgorithm.h /usr/local/include/GammaTriggerAlgorithm.h /usr/local/include/TriggerMaker.h

fi

cd $savedir
