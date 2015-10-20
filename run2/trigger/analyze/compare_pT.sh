#!/bin/bash

doprint="--print"
doprint=""

./compare_pt.py $doprint \
	--1 _data1_run2_trigger_2015-10-20_hardQCD_default_emctrig_out_femc_1.0.root,jets_hard_EMC,"5 TeV R=0.4 f=1.0" \
	--2 _data1_run2_trigger_2015-10-20_hardQCD_default_emctrig_out_femc_0.1.root,jets_hard_EMC,"f=0.1" \
	--3 5TeV-hardQCD-mult-0-default_emctrig_out.root,jets_hard_EMC,"low stats" -b

./compare_pt.py $doprint \
	--1 _data1_run2_trigger_2015-10-20_hardQCD_default_emctrig_out_femc_1.0.root,jets_hard_EMC,"5 TeV R=0.4 f=1.0" \
	--2 _data1_run2_trigger_2015-10-20_hardQCD_default_emctrig_out_femc_1.0.root,jets_hard_EMCc,"within EMC" \
	--3 _data1_run2_trigger_2015-10-20_hardQCD_default_emctrig_out_femc_1.0.root,jets_hard_DMCc,"within DMC"

#./compare_pt.py $doprint \
#	--1 2.76TeV-hardQCD-mult-0-default_emctrig_out.root,jets_hard_EMC,"2.76 TeV R=0.4" \
#	--2 5TeV-hardQCD-mult-0-default_emctrig_out.root,jets_hard_EMC,"5 TeV R=0.4" -b
#
#./compare_pt.py $doprint \
#	--1 2.76TeV-hardQCD-mult-0-default_emctrig_out.root,jets_hard_EMCc,"2.76 TeV R=0.4 in EMCal" \
#	--2 2.76TeV-hardQCD-mult-0-default_emctrig_out.root,jets_hard_DMCc,"2.76 R=0.4 in DCal" \
#	--3 5TeV-hardQCD-mult-0-default_emctrig_out.root,jets_hard_EMCc,"5 TeV R=0.4 in EMCal" \
#	--4 5TeV-hardQCD-mult-0-default_emctrig_out.root,jets_hard_DMCc,"5 TeV R=0.4 in DCal" -b

#./compare_pt.py $doprint \
#	--1 5TeV-hardQCD-mult-0-default_emctrig_out.root,jets_hard_EMC,"5 TeV R=0.4 " \
#	--2 5TeV-hardQCD-mult-0-default_emctrig_out.root,jets_hard_EMCc,"5 TeV R=0.4 in EMCal" \
#	--3 5TeV-hardQCD-mult-0-default_emctrig_out.root,jets_hard_DMCc,"5 TeV R=0.4 in DCal"

#./compare_pt.py $doprint --ymin 1e-10 \
#	--1 5TeV-photons-mult-0-default_emctrig_out.root,tnj_photon_ALL,"#gamma^{prompt} 5 TeV" \
#	--2 5TeV-photons-mult-0-default_emctrig_out.root,tnj_photon_EMC,"#gamma^{prompt} EMCal" \
#	--3 5TeV-photons-mult-0-default_emctrig_out.root,tnj_photon_DMC,"#gamma^{prompt} DCal" -b
#
#./compare_pt.py $doprint --ymin 1e-10 \
#	--1 2.76TeV-photons-mult-0-default_emctrig_out.root,tnj_photon_ALL,"#gamma^{prompt} 2.76 TeV" \
#	--2 5TeV-photons-mult-0-default_emctrig_out.root,tnj_photon_ALL,"#gamma^{prompt} 5 TeV"
