#!/bin/bash

function exec_lbnlcern()
{
	alice
	. $HOME/devel/subjets/bin/setenv_all.sh
	. $HOME/devel/subjets/pythia8/setenv.sh
	export PYTHIA8LOCATION=$PYTHIA8DIR
}

function exec_darwin()
{
	setroot
	pythia8	
}

hostid=`uname -a`
case $hostid in
    *.nersc*)
        [ "$NERSC_HOST" == "pdsf" ] && exec_pdsf
        [ "$NERSC_HOST" == "carver" ] && exec_carver
        hostn=`uname -n`
        case $hostn in
            pc*)
                exec_pdsf
                ;;
        esac
        ;;
    *Darwin*)
        exec_darwin
        ;;
    *lbnl?core*)
        exec_lbnlcern
        ;;
    *)
        exec_default
        ;;
esac



