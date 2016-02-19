#!/usr/bin/env python

import math
import sys
import string

def hextobinary(hex_string):
    binary = lambda x: ' '.join(reversed( [i+j for i,j in zip( *[ ["{0:04b}".format(int(c,16)) for c in reversed('0'+x)][n::2] for n in [1,0] ] ) ] ))
    return binary(hex_string)

def bits(ins):
    sets = []
    ins = ins.replace(' ', '')
    for i in range(len(ins)):
        if ins[len(ins) - i - 1] == '1':
            sets.append(str(i))
    #return ' '.join(reversed(sets))
    return ' '.join(reversed([string.rjust(s, 2) for s in sets]))

def bits_from1(ins):
    sets = []
    ins = ins.replace(' ', '')
    for i in range(len(ins)):
        if ins[len(ins) - i - 1] == '1':
            sets.append(str(i+1))
    #return ' '.join(reversed(sets))
    return ' '.join(reversed([string.rjust(s, 2) for s in sets]))
        
def main():
    arg = ''
    try:
        arg = sys.argv[1]
    except:
        print '[i] usage:',sys.argv[0],'<hexvalue>'
        return
    try:
        bins = hextobinary(arg.lstrip('0x'))
        print '[i] binary is                :',bins
        print '    bits set (first bit at 0)  :', bits(bins)
        print '    bits set (first bit at 1)  :', bits_from1(bins)
    except:
        print '[e] converion failed... are you sure that >',arg,'< is a hex number?'

if __name__=="__main__":
    main()
