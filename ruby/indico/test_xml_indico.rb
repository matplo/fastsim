#!/usr/bin/env ruby

require 'rubygems'
require 'xmlsimple'

xml_data = 

data = XmlSimple.xml_in(xml_data)
print data

data['Result'].each do |item|
   item.sort.each do |k, v|
      if ["Title", "Url"].include? k
         print "#{v[0]}" if k=="Title"
         print " => #{v[0]}\n" if k=="Url"
      end
   end
end
