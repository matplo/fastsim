    for e2 in td2.entries:
        print e2
        td3 = td2.top_n(topn, 3, e2.dir)
        for e3 in td3.entries:
            print '|->',e3

    td1     = entries.top_n(topn, 1)
    print td1
    for e1 in td1.entries:
        print e1
        td2 = entries.top_n(topn, 2, e1.dir)        
        for e2 in td2.entries:
            print ' ',e2
    #td2 = entries.top_n(topn, 2)
            
