#!/bin/bash

savedir=$PWD

if [ ! -z "$SUBJDIR" ]; then
    cd $SUBJDIR

    $SUBJDIR/bin/patch_scripts.py $SUBJDIR '#load_modules' $SUBJDIR/load_modules.sh
    echo "[i] done."
    
    cd $savedir
else
    echo "SUBJDIR not set. call set_env_all.sh or setup manually..."
fi

