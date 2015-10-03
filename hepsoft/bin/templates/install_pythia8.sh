#!/bin/bash

[ -z "$LHAPDFDIR" ] && echo "[error] needs LHAPDFDIR" && exit 1
fjpath=`fastjet-config --prefix`
[ -z "$fjpath" ] && echo "[error] needs fastjet-config" && exit 1

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

function exec_configure()
{
    rsys=`root-config --prefix`
    rsysinc=`root-config --incdir`
    rsyslib=`root-config --libdir`
    ./configure --prefix=$install_dir \
        --enable-shared \
        --with-root=$rsys \
        --with-root-lib=$rsyslib \
        --with-root-include=$rsysinc \
        --with-hepmc2=$HEPMCDIR \
        --with-fastjet3=$fjpath
}

function write_setup_script()
{
    fname=setenv_pythia_$2.sh
    outdir=$1/bin
    #outfile=$outdir/$fname
    mkdir -p $XDIR/scripts 
    outfile=$XDIR/scripts/$fname
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

    cd $working_dir
    echo $PWD
    echo "[i] will install to: $install_dir"    
    echo "[i] install for PYTHIA version $version"

    fdfile="pythia$version.tgz"
    srcdir="pythia$version"
    echo "[i] file to download: $fdfile"
    echo "[i] source sub dir: $srcdir"    
    if [ -e "./downloads/$fdfile" ]; then
        echo "[i] $fdfile exists - will not download"
    else
        mkdir -p ./downloads
        cd ./downloads
        wget http://home.thep.lu.se/~torbjorn/pythia8/$fdfile
        cd -
    fi
    tar xvf ./downloads/$fdfile
    cd $srcdir

    [ "$2" = "clean" ] && make clean   

    exec_configure $install_dir

    make && make install

    write_setup_script $install_dir $version
fi
cd $savedir
