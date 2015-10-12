#!/bin/bash

module list
module load use.own
module load hepsoft/latest 
module load run2trigger
module list

cd $RUN2EMCTRIGGER/test
ln -s $RUN2EMCTRIGGER/gener/config/toymcpy8.cmnd
otool -L $RUN2EMCTRIGGER/bin/toymcpy8
$RUN2EMCTRIGGER/bin/toymcpy8 -lhc 2>&1 | tee test_toy.log

