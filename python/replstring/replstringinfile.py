#!/usr/bin/env python
import sys
from sys import *
#import os
#from os import popen2
import shutil
import time

def exists(filename):
  try:
    f = open(filename)
    f.close()
    return 1
  except:
    return 0

def replace(inputfile = "", pattern = "", replacement = "", outputfile=""):

  #print "Replacing :",pattern,"to",replacement

  if inputfile == "-stdin":
    fin = stdin
  else:
    fin = open(inputfile, "r")
  text = ""

  iswitchfiles = 0
  if outputfile == inputfile:
    outputfile = outputfile + "_new"
    iswitchfiles = 1
      
  if outputfile == "" or outputfile == "-stdout":
    fout = stdout
  else:
    try:
      fout = open(outputfile, "w")
    except:
      print "No bonus... unable to open output file:",outputfile
      fin.close()
      return

  icount = 0
  while 1:
    text = fin.readline()
    if len(text) == 0:
      break
    li = text.split(pattern)
    result = ""

    if len(li) > 1:
      #print "Found matching line",icount,len(li),li
      icount += 1
      index = 0
      while index < len(li):
        result = result + li[index]
        if index + 1 < len(li):
          result = result + replacement
        index = index + 1
    else:
      result = text;
    fout.writelines(result)
    #print result,
  fin.close()
  fout.close()

  if icount == 0:
    #print "No matches found."
    iswitchfiles == 0
  #else:
    #print "Replaced lines:",icount
    
  if iswitchfiles == 1:
    ##comm = "mv " + outputfile + " " + inputfile
    #print "2exec: ",comm
    ##os.popen2(comm)
    ## wait for os ! - seems to be needed
    ##time.sleep(0.01)
    shutil.move(outputfile, inputfile)
    
def usage():
    print "replstringinfile <infile> <from> [to] [outfile]"
    print "replstringinfile <infile> <from> [to] -stdout"
    print "replstringinfile -stdin <from> [to] -stdout"
    print "replstringinfile -stdin <from> [to] [outfile]"

def makethecall():
  
  litmp = len(sys.argv)
  if litmp < 3:
    usage()
    return 1
  
  if sys.argv[1] == "-h":
    usage()
    return 1      
  
  infile = sys.argv[1]
  patt = sys.argv[2]
  if litmp > 3:
    repl = sys.argv[3]
  else:
    repl = ""
    
  outfile = infile
  if litmp > 4:
    outfile = sys.argv[4]
    
  if infile == "-stdin":
    if infile == outfile:
      outfile = "-stdout"
    replace(infile, patt, repl, outfile)
  else:
    if exists(infile):
      replace(infile, patt, repl, outfile)
    else:
      print "Unable to access input file :",infile
        

makethecall()
