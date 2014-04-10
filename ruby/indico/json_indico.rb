#!/usr/bin/env ruby

require 'rubygems'
require 'json'
require 'pp'
require 'find'

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
  def title ()
    return extract_data_string("title")
  end
  def url ()
    return extract_data_string("url")
  end  
  def location ()
    return extract_data_string("location")
  end
  def time ( what = "start" )
    if what == "start"
      return data["startDate"]["time"].sub(":00", "")
    else
      return data["endDate"]["time"].sub(":00", "")
    end
  end
  def time_table()
    return "not implemented"
  end
end

class IndicoContribution < IndicoEntry
  def data
    @data
  end
  def initialize( input )
    super( input )
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
    begin
      fill_contributions
    rescue      
      @is_valid = false
    end
  end
  def contributions ()
    @contributions
  end
  def fill_contributions ()
    begin
      @data["contributions"].each do |c|
                              co = IndicoContribution.new ( c )
                              @contributions.push( co )
                            end
    rescue
      co = IndicoContribution.new ( {"title" => "No contributions"}.to_json )
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

def process_data( fdata )
  djson = JSON.parse( fdata )
  djson["results"].each do |d|
                    ev = IndicoEvent.new( d )
                    #puts "[i] event is:",ev.is_valid
                    if ev.is_valid
                      puts ev.time_table
                    end
                  end  
end

def load_data( fdata, array)
  djson = JSON.parse( fdata )
  djson["results"].each do |d|
                    ev = IndicoEvent.new( d )
                    #puts "[i] event is:",ev.is_valid
                    if ev.is_valid
                      array.push(ev)
                    end
                  end  
end

def load_file( filename )
  #data = IO.readlines( filename )
  #return JSON.parse( data.join('') )
  file = open( filename )
  data = file.read
  return data
end

def find_files( cdir, pattern )
  file_paths = []
  Find.find(cdir) do |path|
      file_paths << path if path.include? pattern
    end
  return file_paths
end

def process_file( fname )
  #puts "Processing file: " + fname
  fdata = load_file( fname )
  process_data( fdata )
end

if __FILE__ == $0
  if ARGV[0].nil?
            fname = "./data/indico-export-event-191905.json"
            process_file(fname)
  else
    lfiles = find_files(ARGV[0].to_s, "indico-export-event-")
    lfiles.each do |fname|
            process_file(fname)
          end
  end
end
