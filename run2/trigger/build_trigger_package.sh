#!/bin/bash

cdir=$PWD

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
THISDIR=`dirname $THISFILE`

cd $THISDIR/EmcalTriggerFast/src
cmake -DCMAKE_INSTALL_PREFIX=$THISDIR
make clean
make && make install

cd $THISDIR/AliGenFME/src
./clean.sh
cmake -DCMAKE_INSTALL_PREFIX=$THISDIR
make && make install

cd $THISDIR/gener/src
./clean.sh
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=$THISDIR ..
make && make install

cd $cdir
