#!/bin/bash

for outdir in /www/home/wwwroot $HOME/Sites
do
    [ -d "$outdir" ] && ./pagebuilder.py | tee $outdir/index
done
