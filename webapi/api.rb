$:.unshift File.join(File.dirname(__FILE__), '..', 'rbtelldus')
require_relative 'json_converter'
require "sinatra"
require "json"
require 'device'

class Device
    def to_json *arg
        {   type: self.class.to_s,
            id: self.id,
            name: self.name,
            cmd: self.cmds
        }.to_json *arg
    end
end

use JSonConverter

get '/' do

end

get '/device/all' do
    content_type :json
    Device.all.to_json
end

get '/device/:id' do
    content_type :json

    id = params[:id].to_i
    d = Device.new_device id

    d.to_json
end

get '/device/:id/learn' do
  content_type :json
  id = params[:id].to_i
  d = Device.new_device id
  d.learn.to_json
end

get '/device/:id/switch/:status' do
    content_type :json
    id = params[:id].to_i
    status = params[:status]

    s = Device.new_device id
    (status == 'on' ? s.on : s.off).to_json
end

get '/device/:id/dim/:intensity' do
    content_type :json
    id = params[:id].to_i
    intensity = params[:intensity].to_f
    lvl = (intensity/100 * 255).to_i

    d = Device.new_device id
    (d.dim lvl).to_json
end

get '/device/:id/name' do
  content_type :json
  id = params[:id].to_i
  d = Device.new_device id
  d.name.to_json
end

# name = "Lampa 1"
post '/device/:id/name' do
  content_type :json
  id = params[:id].to_i
  name = params[:name]
  d = Device.new_device id
  (d.name = name).to_json
end

get '/device/:id/param/:param' do
  content_type :json
  d = Device.new_device params[:id].to_i
  d[params[:param]].to_json
end

# params = { house ="a" window="b" }
post '/device/:id/params' do
  content_type :json
  parameters = params[:params]
  d = Device.new_device params[:id].to_i
  parameters.each do |key, value|
    d[key] = value
  end
  true.to_json
end

