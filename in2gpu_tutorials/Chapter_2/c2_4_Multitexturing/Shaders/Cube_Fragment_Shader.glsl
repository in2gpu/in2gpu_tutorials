#version 450 core

layout(location = 0) out vec4 out_color;

uniform sampler2D texture1;		// baseTexture
uniform sampler2D texture2;		// secondTexture
uniform sampler2D texture3;		// thirdTexture
uniform sampler2D texture4;		// alphaChanTexture
uniform sampler2D texture5;		// rampTexture
uniform float     Timer;

in vec2 texcoord;

void main()
{
	float offset = Timer * 0.0001;
	
	vec4 baseColour   = texture( texture1, vec2(texcoord.x + offset, texcoord.y));
	vec4 secondColour = texture( texture2, vec2(texcoord.x, texcoord.y - offset));
	vec4 thirdColour  = texture( texture3, vec2(texcoord.x, texcoord.y - offset));
	vec4 aChanColour  = texture( texture4, vec2(texcoord.x, texcoord.y - offset));
	vec4 rampColour   = texture( texture5, vec2(texcoord.x, texcoord.y - offset)); 

	baseColour.a = 0.9;
	//secondColour.a = 0.6;
	rampColour.a = 0.6;

	// combine ramp scrolling up with base texture such that the white value in the ramp is diminished
	vec4 blendedBaseRamp = baseColour - rampColour;

	// select only the particles from the second texture. Do this by setting the fragment's alpha to the value of the alphaChan texture
	vec4 particleColour = vec4(thirdColour.r, thirdColour.g, thirdColour.b, aChanColour.rgb);

	//out_color = secondColour;
	//out_color = blendedBaseRamp;
	//particleColour.a = texcoord.y - offset;
	//out_color = particleColour;

	vec4 secondPartColour = mix(particleColour, secondColour, particleColour.a);
	vec4 partThirdColour = mix(secondPartColour,  thirdColour, secondPartColour.a);
	//out_color = mix(baseColour*0.5, partThirdColour * 1.05, partThirdColour.a);

	vec4 blendedOne   = texture(texture3, vec2(texcoord.x + offset * 0.5, texcoord.y) * 1.8);
	vec4 blendedTwo   = texture(texture1, vec2(texcoord.x, texcoord.y - offset) * 1.5);
	vec4 blendedThree = particleColour;//texture(texture3, vec2(texcoord.x + offset * 0.05, texcoord.y - offset * 0.05) * 2);

	out_color = (blendedOne * blendedTwo * 2) * blendedThree * 2;
}