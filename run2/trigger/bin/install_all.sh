#!/bin/bash

savedir=$PWD

if [ ! -z "$SUBJDIR" ]; then
    cd $SUBJDIR

    $SUBJDIR/bin/make_scripts.sh

    #ifiles=`find . -name "install.sh"`
    ifiles="./pythia8"

    for fn in $ifiles
    do
	echo ""
	echo "[i] executing $fn ------------"
	echo ""
	./$fn 2>&1 | tee $fn.install.log
	echo "    log is in: $fn.log"
	echo "[i] executing $fn done -------"
    done

    for cdir in ./pythia8
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
