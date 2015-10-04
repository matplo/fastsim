#!/bin/bash

XDIR="<dir to be set>"
mkdir -p $XDIR/logs
$XDIR/bin/install_hepmc.sh 		2>&1 | tee $XDIR/logs/install_hepmc.log
$XDIR/bin/install_lhapdf.sh 	2>&1 | tee $XDIR/logs/install_lhapdf.log
$XDIR/bin/install_fastjet.sh	2>&1 | tee $XDIR/logs/install_fastjet.log

. $XDIR/scripts/setenv_fastjet_3.1.2.sh
. $XDIR/scripts/setenv_hepmc_2.06.09.sh
. $XDIR/scripts/setenv_lhapdf_5.9.1.sh

$XDIR/bin/install_pythia8.sh	2>&1 | tee $XDIR/logs/install_pythia8.log
