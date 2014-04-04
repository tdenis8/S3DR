#!/bin/bash

script_root_dir=`pwd`

# ***************************************************
# \brief Generate c++ header files from glsl shaders
# ***************************************************

# Go to shaders directory
cd include/open_gl/object_renderers/shaders/

for in_shader in *.{frag,vert,geom}
do
	if [ "$in_shader" != "*.geom" ]
	then
		out_shader=$(echo "$in_shader" | sed -r 's/frag/hpp/g;s/vert/hpp/g;s/geom/hpp/g')
		xxd -i $in_shader $out_shader
	 	# Convert from unsigned to singed char
	 	cat $out_shader | sed -r 's/unsigned //g' >  "include/$out_shader"
	 	rm $out_shader
	fi
done
