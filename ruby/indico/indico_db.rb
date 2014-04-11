#!/usr/bin/env ruby

require 'rubygems'
require 'zlib'
require 'json'
require 'archive/tar/minitar'

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
    @ttable = Array.new()
    time_table
  end
  def speakers ()
    sa = Array.new()
    @data["speakers"].each do |s|
                       sa.push( s["fullName"] )
                    end
    return sa.join(', ')
  end
  def time_table()
    @ttable.push( "|-   Title       : " + title )
    @ttable.push( "|       Speakers : " + speakers )
    @ttable.push( "|       Date     : " + date )
    @ttable.push( "|       Time     : " + time("start") + " - " + time("end"))
    return @ttable
  end
  def time_table_str()
    return @ttable.join("\n")
  end
end

class IndicoEvent < IndicoEntry
  def data
    @data
  end
  def initialize ( input )
    super( input )
    @is_valid = true
    @ttable = Array.new()
    @contributions = Array.new()
    fill_contributions
    time_table
  end
  def is_valid()
    return @is_valid
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
      @is_valid = false
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
    @ttable.push( "* Title       : " + title )
    @ttable.push( "|    URL      : " + url )
    @ttable.push( "|    Location : " + location )
    @ttable.push( "|    Date     : " + date )
    @ttable.push( "|    Time     : " + time + " - " + time("end"))
    @ttable.push( "| -----------   ")
    if @contributions.length > 0
      @contributions.each do |c|
                      if date == c.date
                        @ttable.push( c.time_table )
                      end
                    end
    end
    return @ttable
  end
  def time_table_str()
    return @ttable.join("\n")
  end
end

class IndicoDB
  include Enumerable
  def initialize( tfile = "./data.tar.gz")
    @tarfile = tfile
    @data = Array.new()
    ungzip("indico-export-event-")
  end
  def data()
    return @data
  end
  def <<(val)
    @data << val
  end
  def each(&block)
    @data.each(&block)
  end
  def load_data( fdata )
    djson = JSON.parse( fdata )
    djson["results"].each do |d|
                      ev = IndicoEvent.new( d )
                      if ev.is_valid
                        @data.push(ev)
                      end
                    end  
  end
  def ungzip(pattern)
    tgz = Zlib::GzipReader.new(File.open(@tarfile, 'rb'))
    reader = Archive::Tar::Minitar::Reader.new(tgz)
    reader.each_entry do |file|
            puts "loading: " + file.name
            if file.name.include? pattern
              d = file.read
              load_data(d)              
            end
          end
    reader.close # does this do anything?
    tgz.close
    puts "loaded.                                                      "
  end
  def time_table_str()
    @data.each do |e|
           puts e.time_table_str
         end
  end
end

if __FILE__ == $0
  db = IndicoDB.new("./test.tar.gz")
  #db.time_table_str
  db.each do |e|
      puts e.time_table_str
    end
  puts "[i] number of events: " + db.data.length.to_s
end
