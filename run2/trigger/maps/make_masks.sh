#!/bin/bash

ex="./make_maps_hist.py"
pngfiles="emcal.png dcal.png dcalphos_3rdphos.png dcalphos_nophos.png"
for fn in $pngfiles
do
	$ex -f $fn -b
	mv *.root ./files/
done

