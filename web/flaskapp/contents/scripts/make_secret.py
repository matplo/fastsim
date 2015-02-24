#!/usr/bin/env python

import os
secret = os.urandom(24).encode('hex')

thisdir = os.path.dirname(__file__)
configf = thisdir + '/../config/default'

with open(configf) as f:
    contents = f.readlines()

outl = []
for l in [ls.strip('\n') for ls in contents]:
    if 'SECRET_KEY' in l:
        outl.append( 'SECRET_KEY=\''+secret+'\'\n' )
    else:
        outl.append(l +'\n')
        
with open(configf, 'w') as f:
    f.writelines(outl)
