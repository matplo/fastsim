#!/bin/bash

what="*.log"
#what="job.sh.o*"
find . -name $what -exec tail -v -n 200 {} \;

