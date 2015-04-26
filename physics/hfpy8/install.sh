#!/bin/bash

cmake .
make clean
make

ln -s $PYTHIA8LOCATION/lib/lib* .



