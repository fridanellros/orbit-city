#!/usr/bin/env ruby

require_relative 'rbtelldus'
include RbTelldus

puts "START"
puts "-----"
puts number_of_devices
puts get_name(2)
puts get_protocol(2)
puts "-----"
a = methods(2)

puts "-----"
off(2)
puts "cmd off"
puts last_sent_command(2,a)
puts "-----"

sleep(5)

puts "-----"
on(2)
puts "cmd on"
puts last_sent_command(2,a)
puts "-----"

sleep(5)

puts "-----"
dim(2,55)
puts "cmd dim"
puts last_sent_command(2,a)
puts "dimlvl"
puts last_sent_val(2)
puts "-----"

sleep(5)

puts "-----"
dim(2,255)
puts "cmd dim"
puts last_sent_command(2,a)
puts "dimlvl"
puts last_sent_val(2)
puts "-----"

sleep(5)

puts "-----"
off(2)
puts "cmd off"
puts last_sent_command(2,a)
puts "-----"
puts "DONE"
