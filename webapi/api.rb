$:.unshift File.join(File.dirname(__FILE__), '..', 'rbtelldus')
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

class JSonConverter
  def initialize(app)
    @app = app
  end

  def call(env)
    return @app.call(env) unless env['CONTENT_TYPE'] =~ /json/
    body = env['rack.input'].read ; env['rack.input'].rewind
    return @app.call(env) unless body && !body.empty?
    begin
      parsed = JSON.parse body
      env.update 'rack.request.form_hash' => parsed, 'rack.input' => env['rack.input']
    rescue
    end
    @app.call(env)
  end
end

use JSonConverter

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
  content_type :json
  id = params[:id].to_i
  d = Device.new_device id
  d.learn.to_json
end

get '/switch/:id/:status' do
    content_type :json
    id = params[:id].to_i
    status = params[:status]

    s = Device.new_device id
    (status == 'on' ? s.on : s.off).to_json
end

get '/dim/:id/:intensity' do
    content_type :json
    id = params[:id].to_i
    intensity = params[:intensity].to_f
    lvl = (intensity/100 * 255).to_i

    d = Device.new_device id
    (d.dim lvl).to_json
end

get '/name/:id' do
  content_type :json
  id = params[:id].to_i
  d = Device.new_device id
  d.name.to_json
end

post '/name/:id' do
  content_type :json
  id = params[:id].to_i
  name = params[:name]
  d = Device.new_device id
  (d.name = name).to_json
end

get '/param/:id/:param' do
  content_type :json
  d = Device.new_device params[:id].to_i
  d[params[:param]].to_json
end

post '/param/:id/:param' do
  content_type :json
  d = Device.new_device params[:id].to_i
  (d[params[:param]] = params[:value]).to_json
end

