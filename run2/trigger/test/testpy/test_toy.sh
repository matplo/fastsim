#!/bin/bash

module list
module load use.own
module load hepsoft/latest 
module load run2trigger
module list

cd $RUN2EMCTRIGGER/test/testpy
cp $RUN2EMCTRIGGER/toymcpy8/config/toymcpy8.cmnd .
#cp $RUN2EMCTRIGGER/generate/config/toymcpy8.cmnd .
otool -L $RUN2EMCTRIGGER/bin/toymcpy8
$RUN2EMCTRIGGER/bin/toymcpy8 -lhc 2>&1 | tee test_toy.log
