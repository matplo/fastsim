#!/bin/bash

module use $HOME/devel/rootutils/python/modules
module load pyrut
module load hepsoft/latest
module load root
module load glauber

#GlauberMC.exe --in glau_pbpb_ntuple.root --gen --ncoll 1000:1200 --nev 100:300
#GlauberMC.exe --in glau_pbpb_ntuple.root --gen --ncoll 1:1 --nev 0:10000

#GlauberMC.exe --in glau_pbpb_ntuple.root --gen --ncoll 10:10 --nev 0:2000
GlauberMC.exe --in glau_pbpb_ntuple.root --gen --ncoll 20:20 --nev 0:1000

