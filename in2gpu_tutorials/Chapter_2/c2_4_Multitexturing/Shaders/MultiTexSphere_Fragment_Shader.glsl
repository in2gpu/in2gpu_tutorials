#version 450 core

layout(location = 0) out vec4 out_color;

uniform sampler2D nebulaTex1;			
uniform sampler2D nebulaTex2;		
uniform sampler2D nebulaTex3;		
uniform sampler2D alphaChanTex;
uniform sampler2D rampTex;		
uniform float     Timer;

in vec2 texcoord;

void main() {
	float offset = Timer * 0.0001;
	
	vec4 baseColour   = texture( nebulaTex1, vec2(texcoord.x + offset, texcoord.y));
	vec4 secondColour = texture( nebulaTex2,   vec2(texcoord.x, texcoord.y - offset));
	vec4 thirdColour  = texture( nebulaTex3,   vec2(texcoord.x, texcoord.y - offset));
	vec4 aChanColour  = texture( alphaChanTex, vec2(texcoord.x, texcoord.y - offset));
	vec4 rampColour   = texture( rampTex,      vec2(texcoord.x, texcoord.y - offset)); 

	baseColour.a = 0.9;
	rampColour.a = 0.6;

	// combine ramp scrolling up with base texture such that the white value in the ramp is diminished
	vec4 blendedBaseRamp = baseColour - rampColour;

	// select only the particles from the second texture. Do this by setting the fragment's alpha to the value of the alphaChan texture
	vec4 particleColour = vec4(thirdColour.r, thirdColour.g, thirdColour.b, aChanColour.rgb);

	vec4 blendedOne   = texture(nebulaTex3, vec2(texcoord.x + offset * 0.5, texcoord.y) * 1.8);
	vec4 blendedTwo   = texture(nebulaTex1, vec2(texcoord.x, texcoord.y - offset) * 1.5);
	vec4 blendedThree = particleColour;//texture(texture3, vec2(texcoord.x + offset * 0.05, texcoord.y - offset * 0.05) * 2);

	out_color = (blendedOne * blendedTwo * 2) * blendedThree * 2;
}