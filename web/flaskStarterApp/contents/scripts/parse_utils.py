def rreplace(s, old, new, occurrence):
    li = s.rsplit(old, occurrence)
    return new.join(li)
    
def lreplace(s, old, new, occurrence):
    li = s.rsplit(old, occurrence)
    return new.join(li)

def handle_hrefs(s):
    phref   = s.partition('<href:')
    pcol1   = phref[2].partition(':')
    pcol2   = pcol1[2].partition('>')
    target  = pcol1[0]
    link    = pcol2[0]
    old_syn = '<href:{}:{}>'.format(target, link)
    new_syn = '<a href="{}">{}</a>'.format(target, link)
    #new_syn = render_template('section_element_link.html', target=target, link=link)
    news    = s.replace(old_syn, new_syn)
    #print old_syn, new_syn        
    retval  = None
    try:
        if len(pcol2[2]) > 0:
            retval = handle_hrefs(news)
    except:
        pass
    if retval == None:
        retval = news
    return retval

# note: 1 link per line is allowed at present
def default(v, default):
    if v:
        return v
    return default

def handle_page_links(s):
    phref   = s.partition('<href:')
    pcol1   = phref[2].partition(':')
    pcol2   = pcol1[2].partition(':')
    pcol3   = pcol2[2].partition(':')
    pcol4   = pcol3[2].partition(':')
    pcol5   = pcol4[2].partition('>')            
    target  = default(pcol1[0].rsplit('>')[0], None)
    link    = default(pcol2[0].rsplit('>')[0], target)
    group   = default(pcol3[0].rsplit('>')[0], 'Group')
    blank   = default(pcol4[0].rsplit('>')[0], 'False')
    users   = default(pcol5[0].rsplit('>')[0], 'all')
    old_syn = '<href:{}:{}>'.format(target, link)
    new_syn = '<a href="{}">{}</a>'.format(target, link)
    if blank == 'True':
        blank = True
    else:
        blank = False
    if blank == True:
        target = 'http://' + target
    retval    = [group, target, link, blank, users]
    if target == None:
        retval = []
    #print s,'->',retval            
    return retval
