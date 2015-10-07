#!/bin/sh

module list
module load root/v5-34-34 fastjet/3.1.2 hepmc/2.06.09 lhapdf/5.9.1 pythia/8205
module list
echo "LD:"$LD_LIBRARY_PATH
echo "DYLD:"$DYLD_LIBRARY_PATH
cd $RUN2EMCTRIGGER/test
ln -s $RUN2EMCTRIGGER/gener/config/toymcpy8.cmnd
otool -L $RUN2EMCTRIGGER/bin/toymcpy8
$RUN2EMCTRIGGER/bin/toymcpy8 -lhc 2>&1 | tee test_toy.log

