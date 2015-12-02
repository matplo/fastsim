#!/bin/bash

savedir=$PWD

XDIR="<dir to be set>"
PACKAGENAME=glauber

function write_module_file()
{
    version=$2
    outfile=$XDIR/modules/$1
    outdir=`dirname $outfile`
    mkdir -p $outdir
    rm -rf $outfile
    PACKAGENAME=`echo $1 | awk '{print toupper($0)}'`

    cat>>$outfile<<EOF
#%Module
proc ModulesHelp { } {
        global version
        puts stderr "   Setup $PACKAGENAME \$version"
    }

set     version $version
setenv  ${PACKAGENAME}DIR ${XDIR}
setenv  ${PACKAGENAME}_VERSION $2    
prepend-path LD_LIBRARY_PATH 	${XDIR}/lib
prepend-path DYLD_LIBRARY_PATH 	${XDIR}/lib
prepend-path PATH ${XDIR}/bin

#module use $XDIR/modules
module load AliGlauber

EOF
}

write_module_file glauber nover
