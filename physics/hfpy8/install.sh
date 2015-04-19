#!/bin/bash

cmake .
make clean
make

ln -s $PYTHIA8LOCATION/lib/liblhapdfdummy.* .
ln -s $PYTHIA8LOCATION/lib/libpythia8.* .


