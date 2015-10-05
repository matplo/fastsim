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

rm -rfv $THISDIR/EmcalTriggerFast $THISDIR/include $THISDIR/lib $THISDIR/AliGenFME

rm -rfv /usr/local/lib/libEMCALTriggerFast.* /usr/local/include/TriggerBitConfig.h /usr/local/include/TriggerSetup.h /usr/local/include/TriggerMappingEmcalSimple.h /usr/local/include/TriggerChannelMap.h /usr/local/include/TriggerAlgorithm.h /usr/local/include/JetTriggerAlgorithm.h /usr/local/include/GammaTriggerAlgorithm.h /usr/local/include/TriggerMaker.h


cd $cdir
