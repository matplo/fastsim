def test_depr():
    rootdir ='./'
    try:
        rootdir = sys.argv[1]
    except:
        rootdir = './'
    print '[i] rootdir:',rootdir
    stats = get_stats(rootdir)
    for s in stats:
        print 'file:',s['name'],s['stats']

if __name__=='__main__':
    rootdir ='./'
    try:
        rootdir = sys.argv[1]
    except:
        rootdir = './'
    print '[i] rootdir:',rootdir
    wd = WatchDir(rootdir)
    print 'has chaged? >:',wd.has_changed()    
    #print wd
    if '--update' in sys.argv:
        update = True
    wd.write_cache()


    if '--no-update' in sys.argv and wd.stats_cached != None:
        pass
    else:
        wd.write_cache()
