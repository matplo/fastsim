#!/bin/bash

savedir=$PWD

function abspath()
{
  case "${1}" in
    [./]*)
    echo "$(cd ${1%/*}; pwd)/${1##*/}"
    ;;
    *)
    echo "${PWD}/${1}"
    ;;
  esac
}

THISFILE=`abspath $BASH_SOURCE`
XDIR=`dirname $THISFILE`
if [ -L ${THISFILE} ];
then
    target=`readlink $THISFILE`
    XDIR=`dirname $target`
fi

sjdir=$XDIR/..
find $sjdir -name "setenv.sh" -exec rm {} \;
find $sjdir -name "install.sh" -exec rm {} \;
find $sjdir -name "*.log" -exec rm {} \;

for cdir in estruct hepmc jewel lhapdf sandbox
do
    rm -rf $sjdir/$cdir/downloads
done

for cdir in jewel/2.0.1 lhapdf/lhapdf-5.9.1 lhapdf/5.9.1 hepmc/2.06.09 hepmc/HepMC-2.06.09
do
    rm -rf $sjdir/$cdir
done

cd $sjdir/hepmc/read2root
make clean

cd $sjdir/estruct
make clean

cd $savedir
