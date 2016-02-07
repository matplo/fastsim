#!/bin/bash

# set -x

[ -z $RUN2EMCTRIGGER ] && echo "[e] RUN2EMCTRIGGER not set" && exit 1

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

function replace_line 
{
    #echo "[i] replacing "$1" to "$2" in "$3
    tmpfile="$(mktemp replacing.XXXXXX)"
    cp $3 $tmpfile
    grep -v "$1" $tmpfile > $3
    rm -rf $tmpfile
    echo $2 >> $3
}

function write_script 
{
    jobfile="job.sh"
    if is_arg_set "pdsf" ;
    then
	jobfile="job_pdsf.sh"
    fi
    echo "[i] make script for: pThatMin="$1 "pThatMax="$2
    newdir="./hardQCD/$4/bin-$1-$2"
    photons=false
    if is_arg_set "photons"; then 
        photons=true
        newdir="./photons/$4/bin-$1-$2"
    fi
    minbias=false
    if [ $1 == "0" ]; then
        minbias=true
        newdir="./hardQCD/$4/minbias"
    fi
    mkdir -p $newdir
    echo "find \$PWD -name \"$jobfile\" -exec {} \;" > $newdir/../run_all.sh
    chmod +x $newdir/../run_all.sh
    echo "find \$PWD -name \"submit.sh\" -exec {} \;" > $newdir/../submit_all.sh
    chmod +x $newdir/../submit_all.sh
    cd $newdir
    spwd=$PWD
    cp -v $RUN2EMCTRIGGER/generate/13TeV/emctrig.cmnd $RUN2EMCTRIGGER/generate/13TeV/$jobfile $spwd
    cmndfile=$spwd/emctrig.cmnd
    replace_line "Main:numberOfEvents" "Main:numberOfEvents = $3" "$cmndfile"
    replace_line "Beams:eCM"           "Beams:eCM = 13000."        "$cmndfile"
    if $photons; then
        replace_line "PhaseSpace:pTHatMin"  "PhaseSpace:pTHatMin = $1"  "$cmndfile"
        replace_line "PhaseSpace:pTHatMax"  "PhaseSpace:pTHatMax = $2"  "$cmndfile"
        replace_line "HardQCD:all"          "HardQCD:all = off"         "$cmndfile"
        replace_line "PromptPhoton:all"     "PromptPhoton:all = on"     "$cmndfile"
        replace_line "SoftQCD:all"          "SoftQCD:all = off"         "$cmndfile"
    else
        if $minbias; then
            replace_line "SoftQCD:all"         "SoftQCD:all = on"           "$cmndfile"
            replace_line "PromptPhoton:all"    "PromptPhoton:all = off"     "$cmndfile"
            replace_line "HardQCD:all"         "HardQCD:all = off"          "$cmndfile"
            replace_line "PhaseSpace:pTHatMin" "#PhaseSpace:pTHatMin = 0"   "$cmndfile"
            replace_line "PhaseSpace:pTHatMax" "#PhaseSpace:pTHatMax = 0"   "$cmndfile"
        else
            replace_line "PhaseSpace:pTHatMin"  "PhaseSpace:pTHatMin = $1"  "$cmndfile"
            replace_line "PhaseSpace:pTHatMax"  "PhaseSpace:pTHatMax = $2"  "$cmndfile"
            replace_line "SoftQCD:all"          "SoftQCD:all = off"         "$cmndfile"
            replace_line "HardQCD:all"          "HardQCD:all = on"          "$cmndfile"
            replace_line "PromptPhoton:all"     "PromptPhoton:all = off"    "$cmndfile"
        fi
    fi
    spwd="${spwd//\//\\/}"
    sed -i -e "s/rundir=XXX/rundir=${spwd}/" $jobfile
    sed -i -e "s/mult=XXX/mult=${3}/" $jobfile

    chmod +x $jobfile
    echo "#!/bin/bash" > ./submit.sh
    if is_arg_set "pdsf" ;
    then
	#echo "qsub -l h_vmem=2G -P alice -o $PWD -e $PWD -m e -M mploskon@lbl.gov $PWD/$jobfile" >> ./submit.sh
	echo "qsub -P alice -o $PWD -e $PWD -m e -M mploskon@lbl.gov $PWD/$jobfile" >> ./submit.sh
    else
	echo "qsub -o $PWD -e $PWD $PWD/$jobfile" >> ./submit.sh
    fi
    chmod +x ./submit.sh
    if is_arg_set "submit" ;
    then
    	echo "[i] Submitting..."
       ./submit.sh
    fi
    cd - > /dev/null
}

if is_arg_set "submit" ;
then
    echo "[w] you are sure you want to generate and submit in one go? Continue? [N/y]"
    read -e response
    [ "$response" != "y" ] && exit 0
fi

declare -a pThatBins=( 0 2 5 7 10 15 20 30 40 60 80 110 140 180 220 270 1000 )
if is_arg_set "minbias"; then
    declare -a pThatBins=( 0 2 )
fi

mult=$1
[ -z $1 ] && mult=0
nevents=$2
[ -z $2 ] && nevents=1000
#nevents=500

echo "[i] bin edges: "${pThatBins[@]}
echo "[i] number of bins: "$((${#pThatBins[@]}-1))

for bin in `seq 0 ${#pThatBins[@]}`
do
    lobin=$bin
    hibin=$((bin + 1))
    if [ -z "${pThatBins[$hibin]}" ]; then
	break
    else
	write_script ${pThatBins[$lobin]} ${pThatBins[$hibin]} $nevents $mult
    fi
done

# set +x
