#!/bin/bash

savedir=$PWD

XDIR="<dir to be set>"
working_dir="$XDIR/hepmc"
mkdir -p $working_dir

function exec_configure()
{
    ./configure --prefix=$1 --with-momentum=GEV --with-length=CM
}

function write_setup_script()
{
    fname=setenv_hepmc_$2.sh
    outdir=$1/bin
    #outfile=$outdir/$fname
    outfile=$XDIR/bin/$fname
    rm -rf $outfile
    
    cat>>$outfile<<EOF
#!/bin/bash

export HEPMCDIR=$1
export HEPMC_VERSION=$2    
export DYLD_LIBRARY_PATH=\$HEPMCDIR/lib:\$DYLD_LIBRARY_PATH
export LD_LIBRARY_PATH=\$HEPMCDIR/lib:\$LD_LIBRARY_PATH

EOF
}

if [ ! -d "$working_dir" ]; then
    echo "[error] $working_dir does not exist."
else
    version=$1
    [ -z $version ] && version=2.06.09
    install_dir="$working_dir/$version"

    cd $working_dir
    echo $PWD
    echo "[i] will install to: $install_dir"    
    echo "[i] installing HepMC $version"
    fdfile="HepMC-$version.tar.gz"
    srcdir="HepMC-$version"
    echo "[i] file to download: $fdfile"
    echo "[i] source sub dir: $srcdir"
    if [ -e "./downloads/$fdfile" ]; then
        echo "[i] $fdfile exists - will not download"
    else
        mkdir -p ./downloads
        cd ./downloads
        wget http://lcgapp.cern.ch/project/simu/HepMC/download/$fdfile
        cd -
    fi
    tar zxvf ./downloads/$fdfile
    cd $srcdir
    
    [ "$2" = "clean" ] && make clean    
    exec_configure $install_dir
    
    make && make install

    write_setup_script $install_dir $version
fi

cd $savedir
