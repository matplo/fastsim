#!/bin/bash

plib=`root-config --libdir`

if [ -d $plib ]; then
	for i in $plib/lib*.so ; do
		echo $i
		install_name_tool -add_rpath $plib $i
	done	
fi
