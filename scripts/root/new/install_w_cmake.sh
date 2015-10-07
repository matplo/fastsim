#!/bin/bash

function is_arg_in_set
{
	#echo $@
	last1="${@: -1}"
	last2="${@:(-2):1}"
	#echo "last 2nd is:" $last2
	for i in $@ ; do
	    if [[ $i == $last1 ]] ; then
	    	return 0 # this is true
	    fi
		if [[ $i == $last2 ]]; then
			break
		fi
	done
	return 1 # this is false
}

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

function write_module_file()
{
    version=$2
    outfile=$HOME/privatemodules/root/$version
    outdir=`dirname $outfile`
    mkdir -p $outdir
    rm -rf $outfile

    cat>>$outfile<<EOF
#%Module
proc ModulesHelp { } {
        global version
        puts stderr "   Setup root \$version"
    }

set     version $version
setenv  ROOTSYS $1
setenv  ROOTDIR $1
setenv  ROOT_VERSION $2    
prepend-path LD_LIBRARY_PATH $1/lib
prepend-path DYLD_LIBRARY_PATH $1/lib
prepend-path PATH $1/bin

EOF
}

build=false
configure=false
install=false

if is_arg_set "configure"; then configure=true; fi
if is_arg_set "build"; then build=true; configure=true; fi
if is_arg_set "install"; then build=true; configure=true; install=true; fi


echo "[i] configure:"$configure
echo "[i] build:"$build
echo "[i] install:"$install

savedir=$PWD

# from https://root.cern.ch/get-root-sources
# https://root.cern.ch/building-root

wdir=$HOME/software/rootgit

mkdir $wdir
cd $wdir

git clone http://root.cern.ch/git/root.git

#version=v6-05-02
#version=v5-34-32
version=v5-34-34
tdir=$HOME/software/root/$version

cd root
#git tag -l
#git checkout -b $version 
#$version

git checkout tags/$version

if $configure; then

	cd $wdir
	
	dname=`date +"%Y-%m-%d"`
	#bdir="build_$version_$dname"
	bdir="build_$version"
	if is_arg_set "clean"; then
		rm -rf $bdir
	fi
	mkdir -p $bdir
	cd $bdir
	
	cmake $wdir/root
fi

if $build; then

	cmake --build .
fi

if $install; then

	cmake -DCMAKE_INSTALL_PREFIX=$tdir -P cmake_install.cmake
	
	ln -s $tdir/bin/thisroot.sh "/usr/local/bin/root-$version"
fi

write_module_file $tdir $version

cd $savedir


