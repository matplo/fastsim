#!/usr/bin/env python

#pThatmins = [ 5, 10, 15, 20, 25, 30, 40, 50, 70 ]
pThatmins = [ 5, 10, 15]
quark     = [0, 1]
nevents   = 50000

for q in quark:
    for b in pThatmins:
    	for onia in [0,1]:
    		logname = '{}-{}-{}-{}.log'.format(nevents, b, q, onia)
    		print 'root -l -q \"gener.C({},{},{},{})\" > {}'.format(nevents, b, q, onia, logname)
