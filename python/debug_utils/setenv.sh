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

export PYDEBUGUTILS=$XDIR

if [ -z "$PATH" ];
then
    export PATH=$PYDEBUGUTILS
else
    export PATH=$PYDEBUGUTILS:$PATH
fi

if [ -z "$PYTHONPATH" ];
then
    export PYTHONPATH=$PYDEBUGUTILS
else
    export PYTHONPATH=$PYDEBUGUTILS:$PYTHONPATH
fi

