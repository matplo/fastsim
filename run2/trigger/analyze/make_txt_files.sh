#!/bin/bash

find $RUN2EMCTRIGGER/generate/5TeV/photons/mult-10/*/ -name tree*.root | tee photonfiles.txt
find $RUN2EMCTRIGGER/generate/5TeV/hardQCD/mult-10/*/ -name tree*.root | tee hardQCDfiles.txt
