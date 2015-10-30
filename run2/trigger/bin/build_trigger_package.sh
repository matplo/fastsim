#!/bin/bash

args=$@
function is_arg_set
{
        for i in $args ; do
            if [[ $i == $1 ]] ; then
                return 0 #this is true
            fi
        done
        return 1 #this is false
}

savedir=$PWD

if [ -z $RUN2EMCTRIGGER ]; then
  exit
fi

if [ -d $RUN2EMCTRIGGER ]; then
  cd $RUN2EMCTRIGGER

  if is_arg_set "realclean" ;
  then
    rm -rf $RUN2EMCTRIGGER/include/* $RUN2EMCTRIGGER/lib/*
  fi

  for pack in EmcalTriggerFast AliGenFME/src EMCpidPar/src R2Util/src toymcpy8/src analyze/src
  do
    bdir=$RUN2EMCTRIGGER/.build/$pack
    if is_arg_set "realclean" ;
    then
    	rm -rf $bdir
    fi
    mkdir -p $bdir
    cd $bdir
    debug="-DCMAKE_BUILD_TYPE=Release"
    #cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo
    is_arg_set "debug" && debug=-DCMAKE_BUILD_TYPE=Debug
    cmake -DCMAKE_INSTALL_PREFIX=$RUN2EMCTRIGGER $debug $RUN2EMCTRIGGER/$pack
    is_arg_set "clean" && make clean
    is_arg_set "verbose" && verbose="VERBOSE=1"
    make $verbose && make install
  done
fi
cd $savedir
