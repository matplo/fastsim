#!/bin/bash

if [ ! -z "$PYTHIA8LOCATION" ]; then
    cmake .
    make clean
    make
    
    ln -s $PYTHIA8LOCATION/lib/lib* .
else
    echo "PYTHIA8LOCATION not set"
fi


