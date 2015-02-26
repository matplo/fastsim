#!/usr/bin/env python

sline = 'something <href:www.google.com:target> somethingelse <href:ala:bela>'
#sline = 'nothing'

def handle_href(s):
    phref = s.partition('<href:')
    pcol1 = phref[2].partition(':')
    pcol2 = pcol1[2].partition('>')
    link   = pcol1[0]
    target = pcol2[0]
    old_syn = '<href:{}:{}>'.format(link,target)
    new_syn = '<a href="{}">{}</a>'.format(link,target)
    news   = s.replace(old_syn, new_syn)
    retval = None
    try:
        if len(pcol2[2]) > 0:
            retval = handle_href(news)
    except:
        pass
    if retval == None:
        retval = []
        retval.append(news)
    #retval.append([link, target])
    return retval

print handle_href(sline)
#    print s
#    print '=> link:',link,'target:',target
