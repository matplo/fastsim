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

#$RUN2EMCTRIGGER/bin/toymcpy8 --nev 1000 --hardeta --emc --mult 1000. 2>&1 | tee run.log

#$RUN2EMCTRIGGER/bin/toymcpy8 --emc --mult $mult 2>&1 | tee run.log
#$RUN2EMCTRIGGER/bin/toymcpy8 --emc --mult $mult --femc 0.1 2>&1 | tee run.log

#radius=0.2
#$RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --emc-par 2>&1 | tee run.log
#$RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --emc-par --realbg --femc 0.3 2>&1 | tee run.log
#$RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --emc-par --femcpar 2>&1 | tee run.log

radius=0.4
#$RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --emc-par 2>&1 | tee run.log

#$RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --emc-par --realbg --femc 0.3 2>&1 | tee run.log
#$RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --emc-par --realbg --femc 0.7 2>&1 | tee run.log
#$RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --emc-par --realbg --femc 1.0 2>&1 | tee run.log

radius=0.4
#$RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --emc-par --realbg --femcpar 2>&1 | tee run.log
#$RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --mtune 1.2 --emc-par --realbg --femcpar 2>&1 | tee run.log
$RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --mtune 1.0 --emc-par --realbg --femc 0.3 2>&1 | tee run.log

date

cd -

