#!/bin/bash

savedir=$PWD

if [ ! -z "$SUBJDIR" ]; then
    cd $SUBJDIR

    for cdir in ./estruct ./hepmc/read2root ./analysis/base ./analysis/example ./lil/Subjets
    do
	cd $SUBJDIR/$cdir
	make
	cd -
    done

    echo "[i] done."
    
    cd $savedir
else
    echo "SUBJDIR not set. call set_env_all.sh or setup manually..."
fi
