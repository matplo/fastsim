#!/bin/bash

module load use.own
module load run2trigger

cpwd=$PWD

[ ! -z $1 ] && cd $1

pwd

$RUN2EMCTRIGGER/analyze/EMCpid/make_file_list.sh
root -l -b -q $RUN2EMCTRIGGER/analyze/EMCpid/runEMCpid.C\(\"./filelist.txt\"\)

cd $cpwd
