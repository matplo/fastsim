#!/usr/bin/env python

import os
import GeoIP
import urllib2

def info(ip):
    thisf = os.path.abspath(__file__)
    cdir  = os.path.dirname(thisf)
    dataf = os.path.join(cdir.replace('scripts', 'static/mp/data/'),'GeoIP.dat')
    
    ogeo    = GeoIP.open(dataf, GeoIP.GEOIP_STANDARD)
    country = ogeo.country_name_by_addr(ip)
    retval = ' '.join([str(ip),'[',str(country),']'])
    return retval

# from http://commandline.org.uk/python/how-to-find-out-ip-address-in-python/
def public_ip():
    op = urllib2.urlopen('http://ploskon.com/georaw')
    return op.readlines()[0].strip('\n')

if __name__=="__main__":
    ip = public_ip()
    print info(ip)
