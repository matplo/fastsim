#!/usr/bin/env ruby

require 'rubygems'
require 'json'
require 'pp'
require 'find'

def load_file( filename )
  #data = IO.readlines( filename )
  #return JSON.parse( data.join('') )
  file = open( filename )
  data = file.read
  return data
end

require 'find'

#s = "hello, %s. Where is %s?" % ("John","Mary")

def find_files( cdir, pattern )
  file_paths = []
  Find.find(cdir) do |path|
      file_paths << path if path.include? pattern
    end
  return file_paths
end

class IndicoEntry
  def data
    @data
  end
  def initialize( input )
    @data = input
  end
  def extract_data( what )
    begin
      ret = @data[what]
    rescue
      ret = "Failed to extract %s" % (what)
    end
    return ret
  end  
  def extract_data_string( what )
    ret = extract_data ( what )
    if ret == nil
      ret = ""
    end
    return ret.to_s
  end  
  def date ()
    d = "NoDate?"
    begin
      d = @data["startDate"]["date"]
    rescue
      d = "Failed date extraction."
    end
    return d 
  end
end

class IndicoContribution < IndicoEntry
  def data
    @data
  end
  def initialize( input )
    super( input )
  end
  def time ( what = "start" )
    if what == "start"
      return data["startDate"]["time"].sub(":00", "")
    else
      return data["endDate"]["time"].sub(":00", "")
    end
  end
  def speakers ()
    sa = Array.new()
    @data["speakers"].each do |s|
                       sa.push( s["fullName"] )
                    end
    return sa.join(', ')
  end
  def time_table()
    ttable = Array.new()
    ttable.push( "|-   Title       : " + title )
    ttable.push( "|       Speakers : " + speakers )
    ttable.push( "|       Date     : " + date )
    ttable.push( "|       Time     : " + time("start") + " - " + time("end"))
    return ttable.join("\n")
  end
end

class IndicoEvent < IndicoEntry
  def data
    @data
  end
  def is_valid
    @is_valid
  end
  def initialize ( input )
    super( input )
    @is_valid = true
    @contributions = Array.new()
    fill_contributions
    @is_valid = false
  end
  def title ()
    return extract_data_string("title")
  end
  def url ()
    return extract_data_string("url")
  end  
  def location ()
    return extract_data_string("location")
  end
  def contributions ()
    @contributions
  end
  def fill_contributions ()
    @data["contributions"].each do |c|
                            co = IndicoContribution.new ( c )
                            @contributions.push( co )
                         end
  end
  def time ( what = "start" )
    if what == "start"
      return data["startDate"]["time"].sub(":00", "")
    else
      return data["endDate"]["time"].sub(":00", "")
    end
  end
  def date ()
    return data["startDate"]["date"]
  end
  def time_table ()
    ttable = Array.new()
    ttable.push( "* Title       : " + title )
    ttable.push( "|    URL      : " + url )
    ttable.push( "|    Location : " + location )
    ttable.push( "|    Date     : " + date )
    ttable.push( "|    Time     : " + time + " - " + time("end"))
    ttable.push( "| -----------   ")
    if @contributions.length > 0
      @contributions.each do |c|
                      if date == c.date
                        ttable.push( c.time_table )
                      end
                    end
    end
    return ttable.join("\n")
  end
end

puts ARGV[0]

if ARGV[0].nil?
            fname = "./data/indico-export-event-191905.json"
            d = load_file( fname )
            djson = JSON.parse( d )
            ev = IndicoEvent.new( djson )
else
  lfiles = find_files(ARGV[0].to_s, "indico-export-event-")
  lfiles.each do |fname|
          puts "Processing file: " + fname
          d = load_file( fname )
          ev = IndicoEvent.new( d )
          puts ev.is_valid
          if ev.is_valid
            puts ev.time_table
          end
        end
end
#puts ev.title, ev.location, ev.url, "---"
#puts ev.contributions

#djson["results"].each do |x|
#                  pp x["title"]
#                  pp x["location"]
#                  x["contributions"].each do |c|
#                                      pp c["title"]
#                                      c["speakers"].each do |s|
#                                                     pp '  -> by: ' + s["fullName"]
#                                                   end
#                                    end

              #pp x["contributions"][0]["title"]
              #pp x["contributions"][0]["authors"]
#end
#pp d["results"]
#pp d
