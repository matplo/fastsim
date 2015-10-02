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

. $XDIR/load_modules.sh

#assuming the main dir is ../ up
RUN2EMCTRIGGER=`dirname $XDIR`
export RUN2EMCTRIGGER=`cd $RUN2EMCTRIGGER;pwd`

lhapdf_version=5.9.1
export LHAPDFDIR=$SUBJDIR/lhapdf/$lhapdf_version

fastjet_version=3.1.2
export FASTJETDIR=$RUN2EMCTRIGGER/fastjet/$fastjet_version

add_to_path=$LHAPDFDIR/bin:$JEWELDIR/bin:$HEPMC2ROOTDIR/bin:$FASTJETDIR/bin:$RUN2EMCTRIGGER/bin
add_to_ld_path=$LHAPDFDIR/lib:$SJESTRUCTDIR/lib:$HEPMCDIR/lib:$HEPMC2ROOTDIR/lib:$FASTJETDIR/lib:$RUN2EMCTRIGGER/analysis/base/lib

pythia8_version=8205
export PYTHIA8DIR=$RUN2EMCTRIGGER/pythia8/$pythia8_version

add_to_path=$PYTHIA8DIR/bin
add_to_ld_path=$PYTHIA8DIR/lib

if [ -z "$PATH" ];
then
    export PATH=$add_to_path
else
    export PATH=$add_to_path:$PATH
fi

if [ -z "$LD_LIBRARY_PATH" ];
then
    export LD_LIBRARY_PATH=$add_to_ld_path
else
    export LD_LIBRARY_PATH=$add_to_ld_path:$LD_LIBRARY_PATH
fi

if [ -z "$PYTHONPATH" ];
then
    export PYTHONPATH=$LHAPDFDIR/lib/python2.7/site-packages:$HEPMC2ROOTDIR/bin:$RUN2EMCTRIGGER/bin
else
    export PYTHONPATH=$LHAPDFDIR/lib/python2.7/site-packages:$HEPMC2ROOTDIR/bin:$RUN2EMCTRIGGER/bin:$PYTHONPATH
fi

RUTILSDIR=$HOME/devel/rootutils
. $RUTILSDIR/python/2.7/setenv.sh

