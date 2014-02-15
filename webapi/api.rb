require "sinatra"
require "json"
require_relative "../rbtelldus/device"

class Device
    def to_json *arg
        {   type: self.class.to_s,
            id: self.id,
            name: self.name,
            cmd: self.cmds
        }.to_json *arg
    end
end

get '/' do

end

get '/all' do
    content_type :json
    Device.all.to_json
end

get '/:id' do
    content_type :json

    id = params[:id].to_i
    d = Device.new_device id

    d.to_json
end

get '/learn/:id' do
  id = params[:id].to_i
  d = Device.new_device id
  d.learn
end

get '/switch/:id/:status' do
    id = params[:id].to_i
    status = params[:status]

    s = Device.new_device id
    status == 'on' ? s.on : s.off
end

get '/dim/:id/:intensity' do
    id = params[:id].to_i
    intensity = params[:intensity].to_f
    lvl = (intensity/100 * 255).to_i

    d = Device.new_device id
    d.dim lvl
end

get '/name/:id' do
  id = params[:id].to_i
  d = Device.new_device id
  d.name
end

post '/name/:id' do
  id = params[:id].to_i
  name = params[:name]
  d = Device.new_device id
  d.name = name
end

get '/param/:id/:param' do
  d = Device.new_device params[:id].to_i
  d[params[:param]]
end

post '/param/:id/:param' do
  d = Device.new_device params[:id].to_i
  d[params[:param]] = params[:value]
end

