
function exec_carver()
{
    #echo "[i] loading modules for carver"
    export LOAD_MODULE_SYSTEM="carver"
    module unload pgi/12.9
    module load gcc
    module load cmake
    module load python/2.7.1
    #module use /project/projectdirs/alice/software/modulefiles
    #module load alice/root
    module use /project/projectdirs/alice/ploskon/software/modulefiles
    module load root/v5-34-17
}

function exec_pdsf()
{
    #echo "[i] loading modules for pdsf"
    export LOAD_MODULE_SYSTEM="pdsf"
    #this is needed - relying that your account has the defaults
    . $HOME/.profile
    . $HOME/.bash_profile

    #module load gcc/4.3.2
    #module load gcc/4.6.2_64bit
    #module load cmake
    #module load python/2.7.1
    #module use /project/projectdirs/alice/software/modulefiles
    #module load alice/root
    #module use /project/projectdirs/alice/ploskon/software/modulefiles
    #module load root/v5-34-17
    module load python
    module use /project/projectdirs/alice/software/modulefiles
    #module load alice/root/v6.02.08
    module load alice/root/v5.34.26
    export CC=`root-config --cc`
    export CXX=`root-config --cxx`
    module load cmake
}

function exec_default()
{
    # nothing
    #echo "[i] loading modules for default"
    export LOAD_MODULE_SYSTEM="default"
    [ -z "$ROOTSYS" ] && module load root
    module load fastjet
}

function exec_darwin()
{
    # nothing
    #echo "[i] loading modules for darwin"
    export LOAD_MODULE_SYSTEM="darwin"
    [ -z "$ROOTSYS" ] && module load alice/root
}

function exec_lbnlcern()
{
    echo "[i] loading modules for lbnl@cern host"
    export LOAD_MODULE_SYSTEM="lbnlcern"
    [ -e /usr/share/Modules/init ] && source /usr/share/Modules/init
    #module use /cvmfs/alice.cern.ch/x86_64-2.6-gnu-4.1.2/Modules/modulefiles
    #module load AliRoot/vAN-20141112
    #export ROOTSYS=`root-config --prefix`
    #export PATH=$PATH:`root-config --bindir`
    #export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`root-config --libdir`
    #root-config --version    
    module use $HOME/devel/sandbox/scripts/root/modules/linux
    module load v5-34-30
}

#date

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

#module list 2>&1
