
#from https://root.cern.ch/root/roottalk/roottalk11/att-0988/myroot.py

import ROOT as R

##
# @file myroot.py
# @author Yngve Inntjore Levinsen


##
# Simple class extending the TFile objects
# with iteration capability.
class MFile(R.TFile):
    def __init__(self,filename):
        R.TFile.__init__(self,filename)
    def __iter__(self):
        return iter(self.GetListOfObjects())
    def GetListOfObjects(self):
        objects=[]
        for k in self.GetListOfKeys():
            b=self.Get(k.GetName())
            objects.append(b)
        return objects

##
# I define this separately as well, 
# so that it can be used for TTree objects.
def TreeIter(tree):
    return iter(tree.GetListOfBranches())

##
# TTree objects with iteration capability.
class MTree(R.TTree):
    def __init__(self):
        R.TTree.__init__(self)
    def __iter__(self):
        return iter(self.GetListOfBranches())

##
# @warning Slow!
# branch can be a list of branch names, which I think might
# be faster than calling the function for each branch name.
# Still, this is useless for large number of entries
def branch2numpy(tree,branch):
    if type(tree) == R.TTree and type(branch)==list:
        for l in branch:
            if type(l)!=str:
                raise ValueError,"Wrong type: "+str(l)
            if not hasattr(tree,l):
                raise TypeError
    elif type(tree) != R.TTree or type(branch)!=str:
        raise TypeError
    elif not hasattr(tree,branch):
        raise ValueError
    
    import numpy as np
    if type(branch)==list:
        arr=[np.array([]) for i in range(0,len(branch))]
    else:
        arr=np.array([])
    for i in range(0,tree.GetEntries()):
        tree.GetEntry(i)
        if type(branch)==list:
            for i in range(0,len(branch)):
                arr[i]=np.append(arr[i],getattr(tree,branch[i]))
        else:
            arr=np.append(arr,getattr(tree,branch))

    arr=_reshape(arr,tree.GetEntries())
    return arr

def _reshape(array,nentries):
    if type(array)==list:
        for i in range(0,len(array)):
            array[i]=_reshapeOne(array[i],nentries)
    else:
        array=_reshapeOne(array,nentries)
    return array

def _reshapeOne(array,nentries):
    import numpy as np
    if 1.0*len(array)/nentries % 1 != 0:
        raise ValueError
    return np.reshape(array,(nentries,len(array)/nentries))

