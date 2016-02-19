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

outdir=`abspath $THISDIR/../modules`
mkdir -p $outdir
#module use $outdir

templates=`find $THISDIR/templates -name "fastsim*"`
for TMPLATE in $templates
do
    cp $TMPLATE $outdir
    XDIRr="${XDIR//\//\\/}"
    FNAME=`basename $TMPLATE`
    sed -i "" -e "s/<dir to be set>/${XDIRr}/" $outdir/$FNAME

    mkdir -p $HOME/privatemodules
    cp $outdir/$FNAME $HOME/privatemodules
done

mkdir -p $THISDIR/../bin
cp -v $THISDIR/../scripts/build_fastsim.sh $THISDIR/../bin

cd $savedir
