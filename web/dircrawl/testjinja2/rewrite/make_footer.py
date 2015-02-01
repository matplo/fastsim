#!/usr/bin/env python

import sys
import utils

def render_jinja2(f_template, f_link_template, f_links):
    from jinja2 import Template    
    fitems = utils.load_pair_items(f_links)
    footers = []
    for it in fitems:
        fit = Template(utils.load_file(f_link_template))
        footers.append(fit.render(target=it[0],text=it[1]))
    utils.debug(1, 'footers:', footers)
    utils.debug(1, 'joined:', ' '.join(footers))
    footer = Template(utils.load_file(f_template))
    return footer.render(footer_links = ' '.join(footers))

def render(f_template, f_link_template, f_links):
    ins = utils.load_file(f_links).split('#new')
    footers = []
    for s in ins:
        utils.debug(2,'checking:',s)
        pairs = utils.load_pair_items(s, from_file=False)
        utils.debug(2,'        :',pairs)        
        foot = utils.render(f_link_template, pairs)
        footers.append(foot)
    utils.debug(2,'footers are:',footers)
    return utils.replace_pair_wise([['{{ footer_links }}', ''.join(footers)]], f_template)
    #return utils.render(f_template, f_links)
    
if __name__=='__main__':
    utils.set_debug()
    f_template      = 'templates/footer.html'
    f_link_template = 'templates/footer_link.html'
    f_links         = 'footer.desc'
    result = render(f_template, f_link_template, f_links)
    utils.debug(1, 'result:', result)
    print result
