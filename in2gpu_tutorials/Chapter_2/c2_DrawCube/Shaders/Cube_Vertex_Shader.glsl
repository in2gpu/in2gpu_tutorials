#version 450 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;

uniform mat4 projection_matrix, view_matrix;
uniform vec3 rotation;

out vec4 color;

void main()
{

	color = in_color;
	mat4 rotate_x, rotate_y, rotate_z;
	
	rotate_x = mat4(1.0, 0.0, 0.0, 0.0,
					0.0, cos(rotation.x), sin(rotation.x), 0.0,
					0.0, -sin(rotation.x), cos(rotation.x), 0.0,
					0.0, 0.0, 0.0, 1.0);

	rotate_y = mat4(cos(rotation.y), 0.0, -sin(rotation.y), 0.0,
					0.0, 1.0, 0.0, 0.0,
					sin(rotation.y), 0.0, cos(rotation.y), 0.0,
					0.0, 0.0, 0.0, 1.0);

	rotate_z = mat4(cos(rotation.z), -sin(rotation.z), 0.0, 0.0,
					sin(rotation.z), cos(rotation.z), 0.0, 0.0,
					0.0, 0.0, 1.0, 0.0,
					0.0, 0.0, 0.0, 1.0);

	gl_Position = projection_matrix * view_matrix * rotate_y * rotate_x *rotate_z * vec4(in_position, 1);
	
}