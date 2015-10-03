#!/bin/bash

savedir=$PWD

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

THISFILE=`abspath $BASH_SOURCE`
XDIR=`dirname $THISFILE`
if [ -L ${THISFILE} ];
then
    target=`readlink $THISFILE`
    XDIR=`dirname $target`
fi

cd $XDIR
echo $PWD

version=5.9.1
install_dir="$XDIR/$version"
echo "[i] will install to: $install_dir"

echo "[i] getting the PDFsets first..."
get_PDFsets $install_dir

echo "[i] installing lhapdf $version"
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

XDIR=$XDIRLHA
#. $XDIR/../bin/load_modules.sh

#load_modules

make clean
./configure --prefix=$install_dir
make && make install

cd $savedir