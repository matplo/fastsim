#! /bin/bash

starttime=$(date +%s)
outputdir=$(printf "%s/job%d" $1 $SGE_TASK_ID)
cd $outputdir
echo $PWD
ls

# perpare aliphysics module
source /usr/share/Modules/init/bash
module use /project/projectdirs/alice/mfasel/modulefiles
module load mfasel/aliphysics/master

module use /project/projectdirs/alice/ploskon/software/sandbox/run2/analyzeESD/modules
module load run2aesd

cmd=$(printf "aliroot -b -q \'%s(\"files.txt\")\' &> analysis.log" $2)
echo $cmd
eval $cmd 
endtime=$(date +%s)
jobtime=$(echo "$endtime-$starttime" | bc)
echo Done after $jobtime sec
