#!/bin/bash

# set -x

declare -a pThatBins=( 5 7 10 15 20 30 40 60 80 110 140 180 220 270 320 400 )
nevents=1000
#nevents=500

#cmndfile="toymcpy8.cmnd"
cmndfile="toypyPb.cmnd"
jobfile="job.sh"
submit="no"

[ "$1" == "submit" ] && submit="yes"

if [ "$submit" == "yes" ];
then
    echo "[w] you are sure you want to generate and submit in one go? Continue? [N/y]"
    read -e response
    [ "$response" != "y" ] && exit 0
fi

echo "[i] bin edges: "${pThatBins[@]}
echo "[i] number of bins: "$((${#pThatBins[@]}-1))

function replace_line {
    #echo "[i] replacing "$1" to "$2" in "$3
    tmpfile="$(mktemp)"
    cp $3 $tmpfile
    grep -v "$1" $tmpfile > $3
    rm -rf $tmpfile
    echo $2 >> $3
}

function write_script {
    echo "[i] make script for: pThatMin="$1 "pThatMax="$2
    newdir="bin-$1-$2"
    mkdir -p $newdir
    cp *.cc *.cmnd Makefile setup.sh job.sh $newdir
    cd $newdir
    spwd=$PWD
    replace_line "PhaseSpace:pTHatMin" "PhaseSpace:pTHatMin = $1" "$cmndfile"
    replace_line "PhaseSpace:pTHatMax" "PhaseSpace:pTHatMax = $2" "$cmndfile"
    replace_line "Main:numberOfEvents" "Main:numberOfEvents = $3" "$cmndfile"

    #escaping solved otherwise: spwd=`echo $PWD | sed -e s/\\//\\\\\\\\\\//`
    spwd="${spwd//\//\\/}"
    #sed -i.bak -e "s/rundir=XXX/rundir=${spwd}/" $jobfile

    sed -i -e "s/rundir=XXX/rundir=${spwd}/" $jobfile
    #sed -i -e "s/collider=none/collider=-lhc/" $jobfile
    sed -i -e "s/collider=none/collider=--rotate-soft/" $jobfile

    chmod +x ./job.sh
    echo "#!/bin/bash" > ./submit.sh
    echo "qsub -P alice -o $PWD -e $PWD -m e -M mploskon@lbl.gov job.sh" >> ./submit.sh
    chmod +x ./submit.sh
    if [ "$submit" == "yes" ];
    then
	echo "[i] Submitting..."
	./submit.sh
    fi
    cd - > /dev/null
}

for bin in `seq 0 ${#pThatBins[@]}`
do
    lobin=$bin
    hibin=$((bin + 1))
    if [ -z "${pThatBins[$hibin]}" ]; then
	break
    else
	write_script ${pThatBins[$lobin]} ${pThatBins[$hibin]} $nevents
    fi
done

# set +x
