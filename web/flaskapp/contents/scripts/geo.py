def geo(ip):

    import os
    thisf = os.path.abspath(__file__)
    cdir  = os.path.dirname(thisf)
    dataf = os.path.join(cdir.replace('scripts', 'static/mp/data/'),'GeoIP.dat')
    
    import GeoIP
    ogeo    = GeoIP.open(dataf, GeoIP.GEOIP_STANDARD)
    country = ogeo.country_name_by_addr(ip)
    retval = ' '.join([str(ip),'[',str(country),']'])
    return retval

# from http://commandline.org.uk/python/how-to-find-out-ip-address-in-python/
def getNetworkIp():
    import socket
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.connect(('google.com', 0))
    return s.getsockname()[0]

if __name__=="__main__":
    ip = getNetworkIp()
    print geo(ip)
