#!/usr/bin/env python
import sys

def replace(inputstr = "", pattern = "", replacement = ""):
  text = inputstr
  li = text.split(pattern)
  index = 0
  result = ""
  if len(li) > 0:
    while index < len(li):
      #    if li[index] != pattern:
      result = result + li[index];
      if index + 1 < len(li):
        result = result + replacement
        #    print index,li[index]
      index = index + 1
  else:
    result = text;
#  print "this is replaced :",result
  print result

def usage():
    print "replstring <string> <part> <to>"

def makethecall():
    litmp = len(sys.argv)
    if litmp < 3:
        usage()
        return 1

    instr = sys.argv[1]
    patt = sys.argv[2]
    if litmp > 3:
        repl = sys.argv[3]
    else:
        repl = ""

    replace(instr, patt, repl)

makethecall()
