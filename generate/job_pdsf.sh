#!/bin/bash -l

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

$RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --mtune 1.0 --emc-par --realbg --femcpar 2>&1  | tee "run-1.0.log"
$RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --mtune 1.2 --emc-par --realbg --femcpar 2>&1  | tee "run-1.2.log"

date

cd -

