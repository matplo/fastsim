#!/usr/bin/env python

pThatmins = [ 10, 15, 20, 25, 30, 40, 50 ]
quark     = [0, 1]
nevents   = 10000

for q in quark:
    for b in pThatmins:
        logname = '{}-{}-{}.log'.format(nevents, b, q)
        print 'root -l -q \"gener.C({},{},{})\" > {}'.format(nevents, b, q, logname)
