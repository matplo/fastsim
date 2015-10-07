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

bdir=$THISDIR/build
mkdir $bdir
for pack in EmcalTriggerFast AliGenFME gener
do
  cd $bdir
  mkdir $pack
  cd $pack
  cmake -DCMAKE_INSTALL_PREFIX=$THISDIR $THISDIR/$pack/src
  make clean
  make $1 && make install
done

cd $cdir
