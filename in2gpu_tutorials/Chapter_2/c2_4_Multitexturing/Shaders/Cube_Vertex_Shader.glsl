#version 450 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_texture;

uniform mat4 projection_matrix, view_matrix;
uniform vec3 rotation;

out vec2 texcoord;

void main()
{

	texcoord = in_texture;

	gl_Position = projection_matrix * view_matrix * vec4(in_position, 1);
	
}