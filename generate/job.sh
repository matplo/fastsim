#!/bin/bash

module load use.own
module load hepsoft/latest
module load fastsim
module list

date

rundir=XXX
cd $rundir

pwd

nev=$1
# take the config from hte cmnd file
[ -z $nev ] && nev=-1


# the code below makes a 10 GeV uubar-qark events
#time fastsim -nev $nev -pgunid 2 -pgunpt 10.
#for q in 1 2 3 4 5 6 21
#do
#	time fastsim -nev $nev -pgunid $q -pgunpt 1.0 -pgunptmax 100.0 -out parton_$q.root
#done

# this is using the .cmnd file
time fastsim -nev $nev

date

cd -

