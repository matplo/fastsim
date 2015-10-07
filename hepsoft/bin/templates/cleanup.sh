#!/bin/bash

XDIR="<dir to be set>"

if [ ! -d "$XDIR" ]; then
	echo "[error] $XDIR does not exist."
else
	for TDIR in hepmc lhapdf pythia8 fastjet
	do
		rm -rf $XDIR/$TDIR
	done
	for script in "install*.sh" "cleanup.sh" "setenv_*.sh"
	do
		rm -rfv $XDIR/bin/$script
	done
fi
