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

if [ -z $RUN2AESDDIR ]; then
  exit
fi

function load_pdsf()
{
  module use /project/projectdirs/alice/mfasel/modulefiles
  module load mfasel/aliphysics/master
  module load cmake  
}

function load_darwin()
{
  module load hepsoft
  module load root
}

if [ -d $RUN2AESDDIR ]; then
  cd $RUN2AESDDIR

  if is_arg_set "realclean" ;
  then
    rm -rf $RUN2AESDDIR/include/* $RUN2AESDDIR/lib/*
    for ex in analyzeESD
    do
      rm -rf $RUN2AESDDIR/bin/$ex
    done
  fi

  hostid=`uname -a`
  case $hostid in
      *.nersc*)
        [ "$NERSC_HOST" == "pdsf" ] && load_pdsf
        ;;
      *Darwin*)
        load_darwin
        ;;
      *)
        ;;
  esac

  for pack in EmcalTriggerFast src
  do
    bdir=$RUN2AESDDIR/.build/$pack
    if is_arg_set "realclean" ;
    then
    	rm -rf $bdir
    fi
    mkdir -p $bdir
    cd $bdir
    echo $PWD
    debug="-DCMAKE_BUILD_TYPE=Release"
    #cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo
    is_arg_set "debug" && debug=-DCMAKE_BUILD_TYPE=Debug
    cmake -DCMAKE_INSTALL_PREFIX=$RUN2AESDDIR $debug $RUN2AESDDIR/$pack
    is_arg_set "clean" && make clean
    is_arg_set "verbose" && verbose="VERBOSE=1"
    make $verbose && make install
  done
fi
cd $savedir
