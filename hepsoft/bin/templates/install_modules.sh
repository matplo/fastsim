#!/bin/bash

savedir=$PWD

XDIR="<dir to be set>"

#. $XDIR/bin/setenv_all.sh

outfile=$XDIR/modules/latest
rm -rf $outfile

    cat>>$outfile<<EOF
#%Module
proc ModulesHelp { } {
        global version
        puts stderr "   Setup hepsoft modules"
    }

set     version latest

#module load hepsoft/pythia/$PYTHIA8_VERSION
#module load hepsoft/lhapdf/$LHAPDF_VERSION
#module load hepsoft/hepmc/$HEPMC_VERSION
#module load hepsoft/fastjet/$FASTJET_VERSION

module load hepsoft/pythia
module load hepsoft/lhapdf
module load hepsoft/hepmc
module load hepsoft/fastjet

EOF

mdir=$1
[ -z $mdir ] && mdir=$HOME/privatemodules

tdir=$mdir/hepsoft
mkdir -p $tdir
cp -rv $XDIR/modules/* $tdir
