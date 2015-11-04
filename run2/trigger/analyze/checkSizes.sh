#!/bin/bash

sdir=$1
[ ! -d $sdir ] && echo "[i] $sdir does not exist..." && exit 1
spatt="tree-*.root"
echo "[i] checking dir $sdir for $spatt"
find $sdir -name "$spatt" -exec ls -ltrh {} \;
