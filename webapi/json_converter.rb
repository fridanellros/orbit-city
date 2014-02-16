require 'json'

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
      env.update 'rack.request.form_hash' => parsed, 'rack.request.form_input' => env['rack.input']
    rescue
    end
    @app.call(env)
  end
end
