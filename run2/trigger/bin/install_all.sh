#!/bin/bash

savedir=$PWD

if [ ! -z "$RUN2EMCTRIGGER" ]; then
    cd $RUN2EMCTRIGGER

    $RUN2EMCTRIGGER/bin/make_scripts.sh

    #ifiles=`find . -name "install.sh"`
    ifiles="./lhapdf/install.sh ./pythia8/install.sh ./fastjet/install.sh"

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
	cd $RUN2EMCTRIGGER/$cdir
	make
	cd -
    done

    echo "[i] done."
    
    cd $savedir
else
    echo "RUN2EMCTRIGGER not set. call set_env_all.sh or setup manually..."
fi
