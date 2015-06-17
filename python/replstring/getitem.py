#!/usr/bin/env python
import sys
from sys import *

def usage():
    print "getitem [-n num] [-f filename] [-s pattern] [-d delimiter]"
    print "defaults: read from stdin and num = 1, pattern = \'\', delimiter = ' '"

def getArgWith(st = "-o"):
  litmp = len(sys.argv)
  ic = 1
  xtret = "/dupa jasiu"
  while ic < litmp:
    if st == sys.argv[ic]:
      if ic + 1 < litmp:
        xtret = sys.argv[ic+1]
    ic += 1
  return xtret

def makethecall():
    litmp = len(sys.argv)
    if litmp == 2:
        usage()
        return 1

    #print "Nargs:",len(argv)

    inputfile = ""
    inputfile = getArgWith("-f")

    Nitem = 1;
    try:
      Nitem = int(getArgWith("-n"))
    except:
      Nitem = 1

    spatt = getArgWith("-s")

    delim = getArgWith("-d")
    if delim == '/dupa jasiu':
        delim = ''
      
    #print "will read from",inputfile,lineno
    fin = None
    if inputfile == "-stdin" or inputfile == "/dupa jasiu":
        fin = stdin
        ##if inputfile == "/dupa jasiu":
        ##    print "Reading from stdin by default"
    else:
      try:
        fin = open(inputfile, "r")
      except IOError:
        print "Unable to open file"
        exit()

    text = ""
    result = ""
    item = 0
    stlast = ""
    while 1:
        text = fin.readline()
        if text == "":
            break
        s = text.split()
        if len(delim) > 0:
            s = text.split(delim)
        for st in s:
          item = item + 1
          if item == Nitem:
            print st
          if spatt == stlast:
            print st
          stlast = st
    fin.close()
    
if __name__ == "__main__":
    makethecall()
