#!/bin/bash

ex="./make_maps_hist.py"
files="emcal.png dcal.png dcalphos_3rdphos.png dcalphos_nophos.png"
for fn in $files
do
	$ex -f $fn -b
done

