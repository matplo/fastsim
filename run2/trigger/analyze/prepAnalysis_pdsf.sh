#!/bin/bash

#./testAnalysis.py --dir /home/mateusz/devel/sandbox/run2/trigger/generate/5TeV/hardQCD/mult-12 --name qcd-mtune1.2
#./testAnalysis.py --dir /home/mateusz/devel/sandbox/run2/trigger/generate/5TeV/photons/mult-12 --name photons-mtune1.2

#./testAnalysis.py --dir /home/mateusz/devel/sandbox/run2/trigger/generate/5TeV/hardQCD/mult-10 --name qcd-mtune1.0
#./testAnalysis.py --dir /home/mateusz/devel/sandbox/run2/trigger/generate/5TeV/photons/mult-10 --name photons-mtune1.0

#./testAnalysis.py --dir /home/mateusz/devel/sandbox/run2/trigger/generate/5TeV/hardQCD/mult-0.3 --name qcd-mtune1.0-femc0.3
#./testAnalysis.py --dir /home/mateusz/devel/sandbox/run2/trigger/generate/2.76TeV/hardQCD/mult-10 --name qcd-mtune1.0-2.76TeV

bdir=/project/projectdirs/alice/ploskon/software/sandbox/run2/trigger/generate/5TeV

./prepAnalysis.py --dir $bdir/hardQCD/5TeV --name qcd-5TeV --pdsf
./prepAnalysis.py --dir $bdir/photons/5TeV --name pho-5TeV --pdsf
