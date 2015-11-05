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
$RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --mtune 1.0 --emc-par --realbg --femcpar 2>&1 | tee run.log
#$RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --mtune 1.2 --emc-par --realbg --femcpar 2>&1 | tee run.log

date

cd -

