#!/usr/bin/env python

from newnode import *
import debug_utils as dbg

w = Node('world')
n1 = Node('node1', w)
n2 = Node('node2', w)
dbg.debug_obj(w, truncate=500)
#dbg.debug_obj(n1)
#dbg.debug_obj(n2)
w.render()
