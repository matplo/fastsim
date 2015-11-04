#!/bin/bash -l

module load use.own
module load run2trigger
module list

#env
date

rundir=XXX
mult=XXX
niter=$(($mult/1000))
echo "[i] number of iterations:" $niter

cd $rundir

pwd

radius=0.4

## $RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --emc-par --realbg --femcpar 2>&1 | tee run.log
## $RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --mtune 1.0 --emc-par --realbg --femc 0.3 2>&1 | tee run.log
for m in $(seq 1 $niter); do
    echo "[i] iteration: $m"
    $RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --mtune 1.0 --emc-par --realbg --femcpar --out "out-$m.root" --nev 1000 2>&1  | tee "run-$m.log"
    $RUN2EMCTRIGGER/bin/toymcpy8 -R $radius --mtune 1.2 --emc-par --realbg --femcpar --out "out-$m.root" --nev 1000 2>&1  | tee "run-$m.log"
done

date

cd -

