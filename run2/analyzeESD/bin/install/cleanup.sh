#!/bin/bash

savedir=$PWD

XDIR="<dir to be set>"

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

function build()
{
	echo "cleanup build..."
	rm -rfv $XDIR/.build	
}

function include()
{
	echo "cleanup include..."
	rm -rfv $XDIR/include
}

function lib()
{
	echo "cleanup lib..."
	rm -rfv $XDIR/lib
}

function bin()
{
	echo "cleanup bin..."
	fns=`ls $XDIR/bin/*.*`
	for fn in $fns
	do
		fnb=`basename $fn`
		fnbr=$XDIR/bin/$fnb
		if [[ $fnb == "setup.sh" ]] ; then
			echo $fnbr " - skipped " 
		else
			#echo "   will remove:" $fnbr
			rm -rfv $fnbr
		fi
	done
}

function modules()
{
	echo "cleanup modules..."
	rm -rfv $XDIR/modules
}

function scripts()
{
	echo "cleanup scripts..."
	rm -rfv $XDIR/scripts
}

function install()
{
	build
	bin
	lib
	include
}

commands="build include lib scripts bin modules scripts install"

if is_arg_set "all" ;
then
	commands="build include lib scripts bin modules scripts"
	for c in $commands
	do
		$c
	done
else
	for c in $commands
	do
		is_arg_set "$c" && $c
	done
fi

cd $savedir
