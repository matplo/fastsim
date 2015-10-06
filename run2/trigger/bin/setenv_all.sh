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
XDIR=`dirname $THISFILE`
if [ -L ${THISFILE} ];
then
    target=`readlink $THISFILE`
    XDIR=`dirname $target`
fi

#assuming the main dir is ../ up
RUN2EMCTRIGGER=`dirname $XDIR`
export RUN2EMCTRIGGER
#cd $RUN2EMCTRIGGER

setroot
. $HOME/devel/sandbox/hepsoft/bin/setenv_all.sh

export DYLD_LIBRARY_PATH=$RUN2EMCTRIGGER/lib:$DYLD_LIBRARY_PATH
export LD_LIBRARY_PATH=$RUN2EMCTRIGGER/lib:$LD_LIBRARY_PATH
export PATH=$RUN2EMCTRIGGER/bin:$PATH

RUTILSDIR=$HOME/devel/rootutils
. $RUTILSDIR/python/2.7/setenv.sh
