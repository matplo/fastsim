#!/bin/bash

savedir=$PWD

if [ -z $RUN2EMCTRIGGER ]; then
  exit
fi

if [ -d $RUN2EMCTRIGGER ]; then
  cd $RUN2EMCTRIGGER
  for pack in EMCpidPar/src
  do
    rm -v $RUN2EMCTRIGGER/include/EMPartResp.h $RUN2EMCTRIGGER/include/EMCpid.h
    rm -v $RUN2EMCTRIGGER/lib/libEMCpidPar.*
    bdir=$RUN2EMCTRIGGER/.build/$pack
    [ "$1" == "realclean" ] && rm -rf $bdir
    mkdir -p $bdir
    cd $bdir
    cmake -DCMAKE_INSTALL_PREFIX=$RUN2EMCTRIGGER $RUN2EMCTRIGGER/$pack
    [ "$1" == "clean" ] && make clean
    [ "$1" == "verbose" ] && verbose="VERBOSE=1"
    make $verbose && make install
  done
fi
cd $savedir
