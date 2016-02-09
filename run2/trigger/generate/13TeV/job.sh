#!/bin/bash

#. /u/startup/pdsf.profile
module load use.own
module load run2trigger
module list

#env
date

rundir=XXX
mult=XXX

cd $rundir

pwd

radius=0.4

## $RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --emc-par --realbg --femcpar 2>&1 | tee run.log
## $RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --mtune 1.0 --emc-par --realbg --femc 0.3 2>&1 | tee run.log
##$RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --mtune 1.0 --emc-par --realbg --femcpar 2>&1 | tee run.log

#$RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --mtune 1.0 --emc-par --realbg --femc 1.0 2>&1 | tee run.log

#$RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --mtune 1.2 --emc-par --realbg --femcpar 2>&1 | tee run.log
#$RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --mtune 1.5 --emc-par --realbg --femcpar 2>&1 | tee run.log


radius=0.4
#note R=0.2 is also run in the emc-par (emctrip_par_revent.cxx)
#$RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --mtune 1.2 --emc-par --femcpar --disable-background 2>&1 | tee run$radius.log

$RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --mtune 1.2 --emc-par --femc 0.3 --disable-background 2>&1 | tee run$radius.log

date

cd -

