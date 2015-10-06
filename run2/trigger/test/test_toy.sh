#!/bin/bash

cd $RUN2EMCTRIGGER/test
ln -s $RUN2EMCTRIGGER/gener/config/toymcpy8.cmnd
$RUN2EMCTRIGGER/bin/toymcpy8 -lhc 2>&1 | tee test_toy.log

