#!/bin/bash

XDIR="<dir to be set>"

if [ ! -d "$XDIR" ]; then
	echo "[error] $XDIR does not exist."
else
	for TDIR in hepmc lhapdf pythia8 fastjet
	do
	    mkdir -p $XDIR/$TDIR
	done
fi