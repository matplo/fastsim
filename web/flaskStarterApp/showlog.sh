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

if [ -L ${THISFILE} ];
then
    target=`readlink $THISFILE`
    THISDIR=`dirname $target`
fi

n=20
[ ! -z "$1" ] && n=$1
lastLog=`ls -td $THISDIR/logs/* | head -1`
echo "[i] tail $n: $lastLog"
[ -e "$lastLog" ] && tail -n $n $lastLog
