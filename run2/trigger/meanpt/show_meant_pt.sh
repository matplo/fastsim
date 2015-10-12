#!/bin/bash

#cat mean_pt_nch.txt | txt2graph.py --print --wait --xye 1,3,4,5 --root -x "N_{ch}" -y "<p_{T}>" --title "Pb-Pb 2.76 TeV"
txt2graph.py -f mean_pt_nch.txt --print --wait --xye 1,3,4,5 --root -x "N_{ch}" -y "<p_{T}>" --title "Pb-Pb 2.76 TeV"
