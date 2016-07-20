#!/bin/bash

opts='--logy -x #it{p}_{T}#kern[0.1]{(GeV/#it{c})} -y d#sigma/d#it{p}_{T}#kern[0.1]{(pb/GeV)} --root -b'
txt2graph.py -f ./c-pp-2.75.txt --title "c-quark FONLL" $opts
txt2graph.py -f ./b-pp-2.75.txt --title "b-quark FONLL" $opts

