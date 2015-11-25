#!/bin/bash

cdir=$PWD

args=$@
function is_arg_set
{
        for i in $args ; do
            if [[ $i == $1 ]] ; then
                return 0 #this is true
            fi
        done
        return 1 #this is false
}

if is_arg_set "original" ;
then
	addrs="http://users.phys.psu.edu/~malvioli/eventgenerator"
	outdir=<dir to be set>/data/Pbconfigs
	echo "[i] using $addrs -> $outdir"
	mkdir -p $outdir
	cd $outdir
	for i in `seq 1 10`
	do
		n=$i
		size=${#i}
		[ $size == "1" ] && n="0$i"
		fn=pb208-$n.dat
		link=$addrs/$fn
		echo "    getting: "$link
		wget $link
	done
else
	link="http://portal.nersc.gov/project/alice/data/glauber/Pbconfigs.tar.gz"
	outdir=<dir to be set>/data/Pbconfigs
	mkdir -p $outdir
	echo "[i] using $link -> $outdir"
	wget $link
fi

cd $cdir
