#!/bin/bash

module list
module load use.own
module load hepsoft/latest
module load fastsim
module list

cd $FASTSIM/test/
nev=$1
[ -z $nev ] && nev=20000
# the code below makes a 10 GeV uubar-qark events
#time fastsim -nev $nev -pgunid 2 -pgunpt 10.
#time fastsim -nev $nev -pgunid 21 -pgunpt 2. -pgunptmax 100.0
#for q in 1 2 3 4 5 6 21
#do
#	time fastsim -nev $nev -pgunid $q -pgunpt 1.0 -pgunptmax 100.0 -out parton_$q.root
#done

# this is using the .cmnd file
time fastsim -nev $nev --femcpar
