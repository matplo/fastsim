#!/bin/bash

module use $HOME/devel/rootutils/python/modules
module load pyrut
module load hepsoft/latest
module load root
module load glauber

GlauberMC.exe --in glau_pbpb_ntuple.root --gen --ncoll 1:1 --nev 100:300

