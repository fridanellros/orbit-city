# Loads mkmf which is used to make makefiles for Ruby extensions
require 'mkmf'

# Give it a name
extension_name = 'rbtelldus'

# The destination
dir_config(extension_name, '/usr/local/include')

# Add telldus library link
have_library('telldus-core')

# Do the work
create_makefile(extension_name)
