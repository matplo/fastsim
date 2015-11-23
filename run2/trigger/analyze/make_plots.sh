#!/bin/bash

isprint="--print"
isprint=""
./plot_trigger.py --in /Volumes/one/data/run2/trigger/2015-11-08/qcd-mtune1.0-list.outputs --bias --rej1e-3 --any $isprint
./plot_trigger.py --in /Volumes/one/data/run2/trigger/2015-11-08/qcd-mtune1.0-list.outputs --bias --rej1e-3 --any $isprint --optional

./plot_trigger.py --in /Volumes/one/data/run2/trigger/2015-11-10/qcd-mtune1.0-femc1.0-list.outputs --bias --rej1e-3 --any


