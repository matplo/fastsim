#!/bin/bash

savedir=$PWD

PACKAGENAME=AliGlauber

XDIR="/Users/ploskon/devel/sandbox/physics/glauber"
working_dir="$XDIR/$PACKAGENAME"
mkdir -p $working_dir

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

function write_setup_script()
{
    fname=setenv_$PACKAGENAME.sh
    outdir=$1/bin
    #outfile=$outdir/$fname
    mkdir -p $XDIR/scripts 
    outfile=$XDIR/scripts/$fname
    rm -rf $outfile

    cat>>$outfile<<EOF
#!/bin/bash

export $PACKAGENAMEDIR=$1
export $PACKAGENAME_VERSION=$2    
export DYLD_LIBRARY_PATH=\$$PACKAGENAMEDIR/lib:\$DYLD_LIBRARY_PATH
export LD_LIBRARY_PATH=\$$PACKAGENAMEDIR/lib:\$LD_LIBRARY_PATH

EOF
}

function write_module_file()
{
    version=$2
    outfile=$XDIR/modules/$PACKAGENAME/$version
    outdir=`dirname $outfile`
    mkdir -p $outdir
    rm -rf $outfile

    cat>>$outfile<<EOF
#%Module
proc ModulesHelp { } {
        global version
        puts stderr "   Setup $PACKAGENAME \$version"
    }

set     version $version
setenv  $PACKAGENAMEDIR $1
setenv  $PACKAGENAME_VERSION $2    
prepend-path LD_LIBRARY_PATH $1/lib
prepend-path DYLD_LIBRARY_PATH $1/lib

EOF
}

function build()
{
    bdir=$XDIR/.build/$PACKAGENAME
    if is_arg_set "realclean" ;
    then
        rm -rf $bdir
    fi
    mkdir -p $bdir
    cd $bdir
    debug="-DCMAKE_BUILD_TYPE=Release"
    #cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo
    is_arg_set "debug" && debug=-DCMAKE_BUILD_TYPE=Debug
    cmake -DCMAKE_INSTALL_PREFIX=$XDIR $debug $XDIR/$PACKAGENAME/src
    is_arg_set "clean" && make clean
    is_arg_set "verbose" && verbose="VERBOSE=1"
    make $verbose && make install
}

if [ ! -d "$working_dir" ]; then
    echo "[error] $working_dir does not exist."
else
    version=$1
    [ -z $version ] && version=0.1
    install_dir="$working_dir/$version"

    cd $working_dir
    echo $PWD
    echo "[i] will install to: $install_dir"    
    echo "[i] installing $PACKAGENAME $version"

    build    

    write_setup_script $install_dir
    write_module_file $install_dir $version
fi

cd $savedir
