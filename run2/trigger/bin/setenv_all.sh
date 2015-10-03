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

. $HOME/devel/sandbox/hepsoft/bin/setenv_all.sh

#assuming the main dir is ../ up
RUN2EMCTRIGGER=`dirname $XDIR`
export RUN2EMCTRIGGER
#cd $RUN2EMCTRIGGER

RUTILSDIR=$HOME/devel/rootutils
. $RUTILSDIR/python/2.7/setenv.sh
