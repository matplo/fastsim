#!/bin/bash

module load hepsoft/latest root

rm test_HFGun_*.pdf
root -l test_HFGun.C -q
#draw_file.py -f hfgun_default_output.root
open test_HFGun_*.pdf