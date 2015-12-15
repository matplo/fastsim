#!/usr/bin/env python

import pyutils as ut
import tutils as tu
import draw_utils as du
import dlist
import ROOT
import os
import IPython
import math
import sys

def main():
	fname = 'histos.root'
	hn = [ 	'Norm_EMCGAHRecalcPatchAmp_TriggerTurnOnCurve_EMCal_EMCEG1',
			'Norm_EMCGAHRecalcPatchAmp_TriggerTurnOnCurve_DCal_DMCEG1',
			'Norm_EMCJEHRecalcPatchAmp_TriggerTurnOnCurve_EMCal_EMCEJ1',
			'Norm_EMCJEHRecalcPatchAmp_TriggerTurnOnCurve_DCal_DMCEJ1'
	]

	#hn = [ 	'Norm_EMCGAHRecalcMaxPatchAmp_TriggerTurnOnCurve_EMCal_EMCEG1',
	#		'Norm_EMCGAHRecalcMaxPatchAmp_TriggerTurnOnCurve_DCal_DMCEG1',
	#		'Norm_EMCJEHRecalcMaxPatchAmp_TriggerTurnOnCurve_EMCal_EMCEJ1',
	#		'Norm_EMCJEHRecalcMaxPatchAmp_TriggerTurnOnCurve_DCal_DMCEJ1'
	#]

	#hn = [ 	'Norm_EMCGAHRecalcMaxPatchAmpSubtracted_TriggerTurnOnCurve_EMCal_EMCEG1',
	#		'Norm_EMCGAHRecalcMaxPatchAmpSubtracted_TriggerTurnOnCurve_DCal_DMCEG1',
	#		'Norm_EMCJEHRecalcMaxPatchAmpSubtracted_TriggerTurnOnCurve_EMCal_EMCEJ1',
	#		'Norm_EMCJEHRecalcMaxPatchAmpSubtracted_TriggerTurnOnCurve_DCal_DMCEJ1'
	#]

	#hn = [ 	'Norm_EMCGAHRecalcMaxPatchAmpSubtracted_EMCal_EMCEG1',
	#		'Norm_EMCGAHRecalcMaxPatchAmpSubtracted_DCal_DMCEG1',
	#		'Norm_EMCJEHRecalcMaxPatchAmpSubtracted_EMCal_EMCEJ1',
	#		'Norm_EMCJEHRecalcMaxPatchAmpSubtracted_DCal_DMCEJ1'
	#]

	htitle = [ 	'EMCal EG1 GA_{patch}', 
				'DCal EG1 GA_{patch}',
				'EMCal JE1 JE_{patch}', 
				'DCal JE1 JE_{patch}', 
	]

	hl = dlist.dlist('salvatore_online_patches')
	for i, hname in enumerate(hn):
		hl.add_from_file(hname, fname, htitle[i], 'l hist')

	hl.make_canvas(600, 600)
	hl.draw(logy=True)
	hl.reset_axis_titles('amplitude (ADC counts)', 'ratio: trigger/MB per event')
	ROOT.gPad.SetLogy()
	hl.self_legend(1, '',0.5033445,0.3582609,0.7040134,0.5582609, tx_size=1.2)
	hl.zoom_axis(0, -200, 1000)
	hl.update()
	tu.gList.append(hl)

if __name__ == '__main__':
	tu.setup_basic_root()
	main()
	if not ut.is_arg_set('-b'):
		IPython.embed()	
