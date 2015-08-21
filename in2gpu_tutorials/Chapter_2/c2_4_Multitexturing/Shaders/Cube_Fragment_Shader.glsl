#version 450 core

layout(location = 0) out vec4 out_color;

uniform sampler2D texture1;		// baseTexture
uniform sampler2D texture2;		// secondTexture
uniform sampler2D texture3;		// alphaChanTexture
uniform sampler2D texture4;		// rampTexture
uniform float     Timer;

in vec2 texcoord;

void main()
{
	
	vec4 baseColour   = texture( texture1, vec2(texcoord.x + Timer*0.0001, texcoord.y));
	vec4 secondColour = texture( texture2, vec2(texcoord.x, texcoord.y - Timer*0.0001));

	vec4 aChanColour  = texture( texture3, vec2(texcoord.x, texcoord.y)); 
	vec4 rampColour   = texture( texture4, vec2(texcoord.x, texcoord.y - Timer*0.0001)); 

	baseColour.a = 0.8;
	secondColour.a = 0.6;
	rampColour.a = 0.75;

	// combine ramp scrolling up with base texture such that the white value in the ramp is diminished
	vec4 blendedBaseRamp = baseColour - rampColour;

	out_color = baseColour - rampColour;
}