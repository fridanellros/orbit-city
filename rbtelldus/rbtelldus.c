// Include the Ruby headers and goodies
#include "ruby.h"
#include "telldus-core.h"

// Defining a space for information and references about the module to be stored internally
VALUE RbTelldus = Qnil;

static VALUE method_on( VALUE self, VALUE id ){
    int id_ = NUM2INT(id);
    return INT2NUM( tdTurnOn( id_ ) );
}

static VALUE method_off( VALUE self, VALUE id ){
    int id_ = NUM2INT(id);
    return INT2NUM( tdTurnOff( id_ ) );
}

static VALUE method_dim( VALUE self, VALUE id, VALUE lvl ){
    int id_ = NUM2INT( id );
    char lvl_ = NUM2CHR( lvl );
    return INT2NUM( tdDim( id_, lvl_ ) );
}

static VALUE method_methods( VALUE self, VALUE id ){
    int id_ = NUM2INT(id);
    int supportedMethods = TELLSTICK_TURNON | TELLSTICK_TURNOFF | TELLSTICK_DIM | TELLSTICK_LEARN;
    return INT2NUM( tdMethods( id_, supportedMethods ) );
}

static VALUE method_learn( VALUE self, VALUE id ){
    int id_ = NUM2INT(id);
    return INT2NUM( tdLearn( id_ ) );
}

static VALUE method_number_of_devices( VALUE self ){
    return INT2NUM( tdGetNumberOfDevices() );
}

static VALUE method_id_from_idx( VALUE self, VALUE idx ){
    int idx_ = NUM2INT( idx );
    return INT2NUM( tdGetDeviceId( idx_ ) );
}

static VALUE method_last_sent_command( VALUE self, VALUE id, VALUE cmds ){
    int id_ = NUM2INT( id );
    int cmds_ = NUM2CHR( cmds );
    return INT2NUM( tdLastSentCommand( id_, cmds_ ) );
}

static VALUE method_last_sent_val( VALUE self, VALUE id ){
    int id_ = NUM2INT(id);
    char* valp = tdLastSentValue( id_ );
    VALUE vals = rb_str_new_cstr( valp );
    tdReleaseString( valp );

    ID id_to_i = rb_intern("to_i");
    VALUE val = rb_funcall( vals, id_to_i, 0 );
    return val;
}

static VALUE method_get_name( VALUE self, VALUE id ){
    int id_ = NUM2INT(id);
    char* namep = tdGetName( id_ );
    VALUE name = rb_str_new_cstr( namep );
    tdReleaseString( namep );
    return name;
}

static VALUE method_set_name ( VALUE self, VALUE id, VALUE name )
{
  int id_ = NUM2INT(id);
  char *name_ = StringValueCStr(name);
  if(tdSetName(id_, name_))
  {
    return Qtrue;
  }
  return Qfalse;
}

static VALUE method_get_param ( VALUE self, VALUE id, VALUE param )
{
  int id_ = NUM2INT(id);
  char *param_ = StringValueCStr(param);
  char *value_ = tdGetDeviceParameter(id_, param_, "Not set");
  VALUE value = rb_str_new_cstr(value_);
  tdReleaseString(value_);
  return value;
}

VALUE method_set_model (VALUE self, VALUE id, VALUE model)
{
  int id_ = NUM2INT(id);
  char *model_ = StringValueCStr(model);
  if(tdSetModel(id_, model_))
    return Qtrue;
  return Qfalse;
}

static VALUE method_get_model(VALUE self, VALUE id)
{
  int id_ = NUM2INT(id);
  char *model_ = tdGetModel(id_);
  VALUE model = rb_str_new_cstr(model_);
  tdReleaseString(model_);
  return model;
}

static VALUE method_set_param ( VALUE self, VALUE id, VALUE param, VALUE value )
{
  int id_ = NUM2INT(id);
  char *param_ = StringValueCStr(param);
  char *value_ = StringValueCStr(value);
  if(tdSetDeviceParameter(id_, param_, value_))
  {
    return Qtrue;
  }
  return Qfalse;
}

static VALUE method_get_protocol(VALUE self, VALUE id)
{
  int id_ = NUM2INT(id);
  char* protocol_ = tdGetProtocol(id_);
  VALUE protocol = rb_str_new_cstr(protocol_);
  tdReleaseString(protocol_);
  return protocol;
}

static VALUE method_set_protocol(VALUE self, VALUE id, VALUE protocol)
{
  int id_ = NUM2INT(id);
  char *protocol_ = StringValueCStr(protocol);
  if(tdSetProtocol(id_, protocol_))
    return Qtrue;
  return Qfalse;
}

static VALUE
method_remove_device(VALUE self, VALUE id)
{
  int id_ = NUM2INT(id);
  if(tdRemoveDevice(id_))
    return Qtrue;
  return Qfalse;
}

static VALUE
method_add_device(VALUE self)
{
  return INT2NUM(tdAddDevice());
}

// The initialization method for this module
void Init_rbtelldus() {
    RbTelldus = rb_define_module("RbTelldus");
    rb_define_method(RbTelldus, "on", method_on, 1);
    rb_define_method(RbTelldus, "off", method_off, 1);
    rb_define_method(RbTelldus, "dim", method_dim, 2);
    rb_define_method(RbTelldus, "methods", method_methods, 1);
    rb_define_method(RbTelldus, "learn", method_learn, 1);
    rb_define_method(RbTelldus, "number_of_devices", method_number_of_devices, 0);
    rb_define_method(RbTelldus, "id_from_idx", method_id_from_idx, 1);
    rb_define_method(RbTelldus, "last_sent_command", method_last_sent_command, 2);
    rb_define_method(RbTelldus, "last_sent_val", method_last_sent_val, 1);
    rb_define_method(RbTelldus, "get_name", method_get_name, 1);
    rb_define_method(RbTelldus, "set_name", method_set_name, 2);
    rb_define_method(RbTelldus, "get_param", method_get_param, 2);
    rb_define_method(RbTelldus, "set_param", method_set_param, 3);
    rb_define_method(RbTelldus, "remove_device", method_remove_device, 1);
    rb_define_method(RbTelldus, "add_device", method_add_device, 0);
    rb_define_method(RbTelldus, "get_model", method_get_model, 1);
    rb_define_method(RbTelldus, "set_model", method_set_model, 2);
    rb_define_method(RbTelldus, "get_protocol", method_get_protocol, 1);
    rb_define_method(RbTelldus, "set_protocol", method_set_protocol, 2);
}


//TODO
// add methods check at object level

//int intNumberOfDevices = tdGetNumberOfDevices();
//for (int i = 0; i < intNumberOfDevices; i++) {
//  int id = tdGetDeviceId( i );
//  char *name = tdGetName( id );
//  printf("%d\t%s\n", id, name);
//  tdReleaseString(name);
//}












