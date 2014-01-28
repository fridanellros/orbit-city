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
    unsigned char lvl_ = NUM2CHR( lvl );
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
    unsigned char* valp = tdLastSentValue( id_ );
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

static VALUE method_get_protocol( VALUE self, VALUE id ){
    int id_ = NUM2INT(id);
    char* pcp = tdGetProtocol( id_ );
    VALUE pc = rb_str_new_cstr( pcp );
    tdReleaseString( pcp );
    return pc;
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
    rb_define_method(RbTelldus, "get_protocol", method_get_protocol, 1);
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












