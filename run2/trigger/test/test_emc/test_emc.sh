#!/bin/bash

module load use.own
module load run2trigger
module list

cd $RUN2EMCTRIGGER/test/test_emc
if [ ! -f "$RUN2EMCTRIGGER/test/test_emc/emctrig.cmnd" ] ; then
	cp -v $RUN2EMCTRIGGER/toymcpy8/config/emctrig.cmnd .
fi
#otool -L $RUN2EMCTRIGGER/bin/toymcpy8
#$RUN2EMCTRIGGER/bin/toymcpy8 -v 10 --nev 1000 --emc --mult 1000. 2>&1 | tee test_emc.log

#$RUN2EMCTRIGGER/bin/toymcpy8 --nev 2000 --emc --mult 1000. 2>&1 | tee test_emc.log
#$RUN2EMCTRIGGER/bin/toymcpy8 --nev 1000 --hardeta --emc --mult 1000. 2>&1 | tee test_emc.log
#$RUN2EMCTRIGGER/bin/toymcpy8 --nev 1000 --emc --mult 1000. 2>&1 | tee test_emc.log

#$RUN2EMCTRIGGER/bin/toymcpy8 -v 0 --nev 100 --hardeta --emc --mult 1000. --femc 0.1 2>&1 | tee test_emc.log
#$RUN2EMCTRIGGER/bin/toymcpy8 -v 10 --nev 100 --hardeta --emc-par --mult 1000. --femc 0.1 2>&1 | tee test_emc.log
#$RUN2EMCTRIGGER/bin/toymcpy8 -v 0 --nev 100 --hardeta --emc-par --femcpar 2>&1 | tee test_emc.log

#$RUN2EMCTRIGGER/bin/toymcpy8 -v 0 --nev 100 --mtune 0.8 --emc-par --femcpar 2>&1 | tee test_emc.log
#$RUN2EMCTRIGGER/bin/toymcpy8 -v 0 --nev 100 			--emc-par --femcpar 2>&1 | tee test_emc.log
#$RUN2EMCTRIGGER/bin/toymcpy8 -v 0 --nev 100 --mtune 1.2 --emc-par --femcpar 2>&1 | tee test_emc.log
#$RUN2EMCTRIGGER/bin/toymcpy8 -v 0 --nev 100 --mtune 2.0 --emc-par --femcpar 2>&1 | tee test_emc.log

#$RUN2EMCTRIGGER/bin/toymcpy8 -v 0 --nev 1000 --mtune 1.0 --emc-par --femcpar 2>&1 | tee test_emc.log

#$RUN2EMCTRIGGER/bin/toymcpy8 -v 0 --nev 1000 --mtune 1.0 --emc-test --realbg 	--out realbg.root 2>&1 | tee test_emc.log
#$RUN2EMCTRIGGER/bin/toymcpy8 -v 0 --nev 1000 --mtune 1.0 --emc-test 			--out boltzman.root 2>&1 | tee test_emc.log

$RUN2EMCTRIGGER/bin/toymcpy8 -v 0 --nev 1000 --mtune 1.2 --emc-test --realbg 	--out realbg.root 2>&1 | tee test_emc.log
