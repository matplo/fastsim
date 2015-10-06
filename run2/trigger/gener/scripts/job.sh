#!/bin/bash

#. /u/startup/pdsf.profile

env
date

rundir=XXX
collider=none

cd $rundir
#. ./setup.sh
make
pwd
./toypyPb.exe $collider -R 0.7 | tee run.log
cd -

