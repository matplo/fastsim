#!/bin/bash

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

cdir=$PWD

cd $THISDIR/EmcalTriggerFast/src
cmake -DCMAKE_INSTALL_PREFIX=$THISDIR
make && make install

cd $cdir
