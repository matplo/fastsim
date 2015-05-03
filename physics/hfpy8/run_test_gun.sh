#!/bin/bash

rm test_HFGun.pdf
root -l test_HFGun.C -q
#draw_file.py -f hfgun_default_output.root
open test_HFGun.pdf