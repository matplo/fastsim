#!/bin/bash

draw_file.py -f t_share.root --logy --y 5e-6:1.5 --dopt "+f1001 hist +a90" --titles --gridx --gridy --png --w 800 --h 400
draw_file.py -f t_share_cent.root --logy --y 5e-6:1.5 --dopt "hist +a90" --titles --gridx --gridy --png --w 800 --h 400
