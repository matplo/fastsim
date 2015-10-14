#!/bin/bash

# set -x

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
    echo "[i] make script for: pThatMin="$1 "pThatMax="$2
    newdir="./hardQCD/mult-$4/bin-$1-$2"
    photons=false
    if is_arg_set "photons"; then 
        photons=true
        newdir="./photons/mult-$4/bin-$1-$2"
    fi
    mkdir -p $newdir
    echo "find $PWD -name \"job.sh\" -exec {} \;" > $newdir/../run_all.sh
    chmod +x $newdir/../run_all.sh
    echo "find $PWD -name \"submit.sh\" -exec {} \;" > $newdir/../submit_all.sh
    chmod +x $newdir/../submit_all.sh
    cd $newdir
    spwd=$PWD
    cp -v $RUN2EMCTRIGGER/generate/5TeV/emctrig.cmnd $RUN2EMCTRIGGER/generate/5TeV/job.sh .
    cmndfile=$spwd/emctrig.cmnd
    replace_line "PhaseSpace:pTHatMin" "PhaseSpace:pTHatMin = $1" "$cmndfile"
    replace_line "PhaseSpace:pTHatMax" "PhaseSpace:pTHatMax = $2" "$cmndfile"
    replace_line "Main:numberOfEvents" "Main:numberOfEvents = $3" "$cmndfile"
    replace_line "Beams:eCM"           "Beams:eCM = 5000."        "$cmndfile"
    if $photons; then
        replace_line "HardQCD:all"      "HardQCD:all = off"       "$cmndfile"
        replace_line "PromptPhoton:all" "PromptPhoton:all = on"   "$cmndfile"
    else
        replace_line "HardQCD:all"      "HardQCD:all = on"        "$cmndfile"
        replace_line "PromptPhoton:all" "PromptPhoton:all = off"  "$cmndfile"
    fi
    spwd="${spwd//\//\\/}"
    sed -i -e "s/rundir=XXX/rundir=${spwd}/" $jobfile
    sed -i -e "s/mult=XXX/mult=${4}/" $jobfile

    chmod +x ./job.sh
    echo "#!/bin/bash" > ./submit.sh
    #echo "qsub -P alice -o $PWD -e $PWD -m e -M mploskon@lbl.gov job.sh" >> ./submit.sh
    echo "qsub -o $PWD -e $PWD $PWD/job.sh" >> ./submit.sh
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

declare -a pThatBins=( 5 7 10 15 20 30 40 60 80 110 140 180 220 270 1000 )
mult=$1
[ -z $1 ] && mult=0
nevents=$2
[ -z $2 ] && nevents=1000
#nevents=500

jobfile="job.sh"

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
