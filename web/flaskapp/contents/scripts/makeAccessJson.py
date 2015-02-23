#!/usr/bin/env python

import datetime
import os

#dt = datetime.datetime.strptime('09/Jan/2015:02:10:42', '%d/%b/%Y:%H:%M:%S')
#print dt

def makeDT(str):
    dt = datetime.datetime.strptime(str, '%d/%b/%Y:%H:%M:%S')
    return dt

class bin:
    def __init__(self,low, high):
        self.content = 0
        self.low  = low
        self.high = high
        self.width = (high-low)
        self.center = low + self.width/2.
    def fill(self,v, w = 1):
        if v >= self.low and v < self.high:
            self.content = self.content + w
    def dump(self):
        print self.low, self.center, self.high, ':', self.content

class hist:
    def __init__(self,low, high, nbins):
        self.low = low
        self.high = high
        self.nbins = nbins
        self.bsize = (high - low) / (1. * nbins)
        self.bins = []
        for i in range(nbins):
            bsl = self.low + (i+0) * self.bsize
            bsh = self.low + (i+1) * self.bsize
            self.bins.append(bin(bsl, bsh))
    def fill(self,v, w=1):
        for b in self.bins:
            b.fill(v, w)
    def dump(self):
        for b in self.bins:
            b.dump()
    def array(self):
        arr = []
        for b in self.bins:
            tx = { "x" : b.center, "y" : b.content }
            arr.append(tx)
        return arr
    def asJSONstring(self):
        import json
        return json.dumps(self.array())

def main(debug=True):
    basedir = os.path.abspath(os.path.dirname(__file__))
    if debug:
        print '[i] working dir:',basedir
    
    fname = basedir + '/../../logs/access.log'
    tstamps = []
    try:
        for l in open(fname).readlines():
            tstamp = l.split('[')[1].split(' ')[0]
            tstamps.append(makeDT(tstamp))
    except:
        if debug:
            print 'no:',fname

    outh = []
    for i in range(0,24):
        outh.append({ "x" : i, "y" : 0 })

    #h = hist(0, 24, 96)
    h = hist(0, 24, 48)
    for ts in tstamps:
        outh[ts.hour]['y'] = outh[ts.hour]['y'] + 1
        t = ts.hour + ts.minute/60.
        h.fill(t)
    #h.dump()
    print h.array()
    print
    #print outh
    #print tstamps
    print h.asJSONstring()
    print
    import json
    if debug:
        print json.dumps(outh)
    outfname = basedir + '/../static/data/access.json'
    with open(outfname, 'w') as f:
        #f.write(json.dumps(outh))
        f.write(h.asJSONstring())
    if debug:
        print '[i] written to:',outfname
    
if __name__=='__main__':
    main()
