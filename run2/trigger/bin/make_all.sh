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

savedir=$PWD

topdir=$XDIR/..
cd $topdir

echo $PWD

. $XDIR/setenv_all.sh

makefiles=`find . -name "makefile"`
echo $makefiles
for m in $makefiles
do
    cd $topdir
    cdir=`dirname $m`
    echo $cdir
    cd $cdir
    make
done

cd $savedir
