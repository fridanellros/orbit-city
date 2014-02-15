require_relative 'rbtelldus'

class Device

  extend RbTelldus

  attr_accessor :id, :cmds

  def self.new_device( id )
    methods = Device.methods( id )
    if methods & 16
      return Dimmer.new( id )
    else
      return Switch.new( id )
    end
  end

  def initialize( id )
    @id = id
    @cmds = Device.methods( self.id )
  end

  def name
    Device.get_name( self.id )
  end

  def name=(n)
    result = Device.set_name( self.id, n )
    if result == true
      return true
    else
      return false
    end
  end

  #params
  def [](param)
    Device.get_param( self.id, param )
  end

  def []=(param, value)
    Device.set_param(self.id, param, value)
  end

  def protocol
    Device.get_protocol( self.id )
  end

  def learn
    Device.learn( self.id )
  end

  def last_command
    Device.last_sent_command( self.id, self.cmds )
  end

  def Device.all
    devlist = []

    ( 0...Device.number_of_devices ).each do | i |
      id = Device.id_from_idx( i )
      devlist << Device.new_device( id )
    end

    return devlist
  end

end

class Switch < Device
  def on
    Device.on( self.id )
  end

  def off
    Device.off( self.id )
  end

end

class Dimmer < Switch
  def dim( lvl )
    Device.dim( self.id, lvl )
  end

  def last_val
    Device.last_sent_val( self.id )
  end

end
