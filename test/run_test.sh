#!/bin/bash

module list
module load use.own
module load hepsoft/latest
module load fastsim
module list

cd $FASTSIM/test/
fastsim.exe 


