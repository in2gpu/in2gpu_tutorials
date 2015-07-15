#version 450 core

layout(location = 0) out vec4 out_color;

uniform sampler2D texture1;

in vec2 texcoord;
void main()
{
	vec4 color = texture(texture1, texcoord);
	out_color = color;
}