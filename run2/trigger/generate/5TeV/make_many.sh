#!/bin/bash

for mult in 0 500 1000 2000 3000 4000 5000
do
    ./make_job_scripts.sh $mult 10000
done

for mult in 0 500 1000 2000 3000 4000 5000
do
    ./make_job_scripts.sh $mult 10000 photons
done
