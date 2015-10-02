#!/bin/bash

savedir=$PWD

if [ ! -z "$RUN2EMCTRIGGER" ]; then
    cd $RUN2EMCTRIGGER

    $RUN2EMCTRIGGER/bin/patch_scripts.py $RUN2EMCTRIGGER '#load_modules' $RUN2EMCTRIGGER/load_modules.sh
    echo "[i] done."
    
    cd $savedir
else
    echo "RUN2EMCTRIGGER not set. call set_env_all.sh or setup manually..."
fi

