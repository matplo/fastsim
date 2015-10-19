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

$RUN2EMCTRIGGER/bin/toymcpy8 --emc --mult $mult 2>&1 | tee run.log
$RUN2EMCTRIGGER/bin/toymcpy8 --emc --mult --femc 0.1 $mult 2>&1 | tee run.log

date

cd -

