#!/bin/bash

#mults="0 500 1000 2500 4000 5000"
mults="0 2000 4000"
for mult in $mults
do
    ./make_job_scripts.sh $mult 10000
done

for mult in $mults
do
    ./make_job_scripts.sh $mult 10000 photons
done
