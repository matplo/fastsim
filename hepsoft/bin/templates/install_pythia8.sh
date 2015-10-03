#!/bin/bash

[ -z "$LHAPDFDIR" ] && echo "[e] needs LHAPDFDIR" && exit 1

savedir=$PWD

XDIR="<dir to be set>"
working_dir="$XDIR/pythia"
mkdir -p $working_dir

function abspath()
{
  case "${1}" in
    [./]*)
    echo "$(cd ${1%/*}; pwd)/${1##*/}"
    ;;
    *)
    echo "${PWD}/${1}"
    ;;
  esac
}

THISFILE=`abspath $BASH_SOURCE`
XDIR=`dirname $THISFILE`
cd $XDIR

unction write_setup_script()
{
    fname=setenv_pythia_$2.sh
    outdir=$1/bin
    #outfile=$outdir/$fname
    outfile=$XDIR/bin/$fname
    rm -rf $outfile

    cat>>$outfile<<EOF
#!/bin/bash

export PYTHIA8DIR=$1
export PYTHIA8_VERSION=$2    
export DYLD_LIBRARY_PATH=\$PYTHIA8DIR/lib:\$DYLD_LIBRARY_PATH
export LD_LIBRARY_PATH=\$PYTHIA8DIR/lib:\$LD_LIBRARY_PATH
export PATH=\$PYTHIA8DIR/bin:\$PATH
EOF
}


if [ ! -d "$working_dir" ]; then
    echo "[error] $working_dir does not exist."
else
    version=$1
    [ -z $version ] && version=8205
    install_dir="$working_dir/$version"

    echo "[i] install for PYTHIA version $version"
    fdfile="pythia$version.tgz"
    if [ -e "./downloads/$fdfile" ]; then
        echo "[i] ./downloads/$fdfile exists - will not download"
    else
        mkdir -p ./downloads
        cd ./downloads
        wget http://home.thep.lu.se/~torbjorn/pythia8/$fdfile
        cd -
    fi
    #rm -rf ./$version
    #mkdir -p ./$version
    #cd ./$version
    mkdir ./tmp
    cd ./tmp
    tar xvf ../downloads/$fdfile
    cd pythia$version
    #./configure --prefix=$XDIR/$version --enable-shared --with-root=$ROOTSYS --with-hepmc2=$HEPMCDIR --with-lhapdf5=$LHAPDFDIR
    ./configure --prefix=$XDIR/$version --enable-shared --with-root=$ROOTSYS --with-hepmc2=$HEPMCDIR --with-fastjet3=$PYTHIA8DIR
    make
    make install
    #cp -v ../misc/Makefile .
    #echo $PWD
    #make
fi
cd $savedir
