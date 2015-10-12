#!/bin/bash

module load use.own
module load run2trigger
module list

cd $RUN2EMCTRIGGER/test/test_emc
if [ ! -f "$RUN2EMCTRIGGER/test/test_emc/emctrig.cmnd" ] ; then
	cp -v $RUN2EMCTRIGGER/gener/config/emctrig.cmnd .
fi
#otool -L $RUN2EMCTRIGGER/bin/toymcpy8
$RUN2EMCTRIGGER/bin/toymcpy8 --emc -lhc 2>&1 | tee test_emc.log

