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

savedir=$PWD

THISFILE=`abspath $BASH_SOURCE`
XDIR=`dirname $THISFILE`
if [ -L ${THISFILE} ];
then
    target=`readlink $THISFILE`
    XDIR=`dirname $target`
fi

THISDIR=$XDIR
XDIR=`dirname $XDIR`

[ ! -z $1 ] && XDIR=$1

[ ! -d $XDIR ] && mkdir -p $XDIR

if [ -d $XDIR ]; then
    cd $XDIR
    echo "[i] setup in $PWD"
else
    echo "[error] $XDIR does not exist. stop here."
fi

install=`find $THISDIR/install -name "*.sh"`
for TMPLATE in $install
do
    cp $TMPLATE $THISDIR
    XDIRr="${XDIR//\//\\/}"
    FNAME=`basename $TMPLATE`
    sed -i "" -e "s/<dir to be set>/${XDIRr}/" $THISDIR/$FNAME
done

$THISDIR/make_module.sh

cd $savedir
