#! /bin/bash

#rID=000244982
rID=000245146
OUTDIR=$PWD/output$rID

FILENAME=`readlink -f $0`
BASE=`dirname $FILENAME`

filelistdir=$BASE/filelists
filelist="$filelistdir/files_$rID.txt"
python $BASE/submit.py -i $filelist -o $OUTDIR -n 100 -m $BASE/runLocal.C
