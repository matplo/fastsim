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

if [ -z $FASTSIM ]; then
  exit
fi

if [ -d $FASTSIM ]; then
  cd $FASTSIM

  if is_arg_set "realclean" ;
  then
    rm -rf $FASTSIM/include/* $FASTSIM/lib/*
    for ex in testETF channelmaptester toymcpy8 filter_single_entries
    do
      rm -rf $FASTSIM/bin/$ex
    done
  fi

#  for pack in AliGenFME/src src
#  for pack in wrapper/src rutil/src src
#  for pack in rutil/src src
  for pack in src
  do
    bdir=$FASTSIM/.build/$pack
    if is_arg_set "realclean" ;
    then
    	rm -rf $bdir
    fi
    mkdir -p $bdir
    cd $bdir
    debug="-DCMAKE_BUILD_TYPE=Release"
    #cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo
    #is_arg_set "o3" && export CXXFLAGS=-O3 # Release does it
    is_arg_set "debug" && debug=-DCMAKE_BUILD_TYPE=Debug
    #is_arg_set "debug" && extracxx=-ftrapping-math -fsignaling-nans $CXXFLAGS
    is_arg_set "debug" && extracxx=-fsignaling-nans
    cmake -DCMAKE_INSTALL_PREFIX=$FASTSIM $debug -DCMAKE_CXX_FLAGS=$extracxx $FASTSIM/$pack
    is_arg_set "clean" && make clean
    is_arg_set "verbose" && verbose="VERBOSE=1"
    make $verbose && make install
  done
fi
cd $savedir
