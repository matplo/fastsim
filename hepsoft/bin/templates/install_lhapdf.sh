#!/bin/bash

savedir=$PWD

XDIR="<dir to be set>"
working_dir="$XDIR/lhapdf"
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

function get_PDFsets()
{
    cdir=$PWD
    if [ -e "./downloads/PDFsets.tar.gz" ]; then
	echo "[i] ./downloads/PDFsets.tar.gz exists - will not download"
    else
	mkdir -p ./downloads
	cd ./downloads
	wget --no-check-certificate https://dl.dropboxusercontent.com/u/14190654/PDFsets/PDFsets.tar.gz
	cd -
    fi
    pdfsetdir=$1/share/lhapdf
    mkdir -p $pdfsetdir
    cd $pdfsetdir
    tar zxvf $cdir/downloads/PDFsets.tar.gz
    ls -ltr $pdfsetdir/PDFsets
    echo "[i] installing PDFsets done."
    cd $cdir
    echo $PWD
}

function write_setup_script()
{
    fname=setenv_lhapdf_$2.sh
    outdir=$1/bin
    #outfile=$outdir/$fname
    mkdir -p $XDIR/scripts 
    outfile=$XDIR/scripts/$fname
    rm -rf $outfile

    cat>>$outfile<<EOF
#!/bin/bash

export LHAPDFDIR=$1
export LHAPDF_VERSION=$2    
export DYLD_LIBRARY_PATH=\$LHAPDFDIR/lib:\$DYLD_LIBRARY_PATH
export LD_LIBRARY_PATH=\$LHAPDFDIR/lib:\$LD_LIBRARY_PATH
export PATH=\$LHAPDFDIR/bin:\$PATH
EOF
}

function write_module_file()
{
    version=$2
    outfile=$XDIR/modules/lhapdf/$version
    outdir=`dirname $outfile`
    mkdir -p $outdir
    rm -rf $outfile

    cat>>$outfile<<EOF
#%Module
proc ModulesHelp { } {
        global version
        puts stderr "   Setup lhapdf \$version"
    }

set     version $version
setenv  LHAPDFDIR $1
setenv  LHAPDF_VERSION $2    
prepend-path LD_LIBRARY_PATH $1/lib
prepend-path DYLD_LIBRARY_PATH $1/lib
prepend-path PATH $1/bin

EOF
}

if [ ! -d "$working_dir" ]; then
    echo "[error] $working_dir does not exist."
else
    version=$1
    [ -z $version ] && version=5.9.1
    install_dir="$working_dir/$version"

    cd $working_dir
    echo $PWD
    echo "[i] will install to: $install_dir"    
    echo "[i] installing lhapdf $version"
    echo "[i] getting the PDFsets first..."
    get_PDFsets $install_dir
    fdfile="lhapdf-$version.tar.gz"
    srcdir="lhapdf-$version"
    echo "[i] file to download: $fdfile"
    echo "[i] source sub dir: $srcdir"
    
    if [ -e "./downloads/$fdfile" ]; then
        echo "[i] ./downloads/$fdfile exists - will not download"
    else
        mkdir -p ./downloads
        cd ./downloads
        wget http://www.hepforge.org/archive/lhapdf/$fdfile
        cd -
    fi
    
    tar zxvf ./downloads/$fdfile
    cd $srcdir
    
    [ "$2" = "clean" ] && make clean    

    ./configure --prefix=$install_dir
    make && make install
    write_setup_script $install_dir $version
    write_module_file $install_dir $version
fi

cd $savedir