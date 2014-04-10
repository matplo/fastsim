#!/usr/bin/env ruby

require 'rubygems'
require 'rubygems/package'
require 'zlib'
require 'fileutils'
require 'pp'
require './json_indico'
require 'archive/tar/minitar'

#from: https://gist.github.com/sinisterchipmunk/1335041
def ungzip_from_web(tarfile)
  z = Zlib::GzipReader.new(tarfile)
  unzipped = StringIO.new(z.read)
  z.close
  return unzipped
end

def ungzip_mp(tarfile)
  f = File.open(tarfile)
  gz = Zlib::GzipReader.new(f)
  data = gz.read
  gz.close
  return data
end

def ungzip_failed(tarfile)
  #require 'archive/tar'
  data = []
  arch = Archive::Tar.traverse(tarfile, :compression => :gzip) do |header, contents|
           puts header[:path]
           data.push(contents)
         end
  return data
end

def ungzip(tarfile, pattern)
  data = []
  tgz = Zlib::GzipReader.new(File.open(tarfile, 'rb'))
  reader = Archive::Tar::Minitar::Reader.new(tgz)
  reader.each_entry do |file|
          #do something with each file, and break if you like
          print "loading... " + file.name + "    \r"
          if file.name.include? pattern
            load_data(file.read, data)
          end
        end
  reader.close # does this do anything?
  tgz.close
  puts "loaded                                 "
  return data
end

def load_file( filename )
  #data = IO.readlines( filename )
  #return JSON.parse( data.join('') )
  file = open( filename )
  data = file.read
  return data
end

if __FILE__ == $0
  if ARGV[0].nil?
    fname = "./data.tar.gz"
    #fname = "./data/indico-export-event-192026.json.gz"
  else
    fname = ""
  end
  if not fname.nil?
    data = ungzip(fname, "indico-export-event-")
    data.each do |ev|
          puts ev.time_table
        end
  end
end
