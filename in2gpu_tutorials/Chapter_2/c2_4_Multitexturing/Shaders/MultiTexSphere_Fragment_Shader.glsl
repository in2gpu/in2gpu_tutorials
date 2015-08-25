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
	
	vec4 firstColour  = texture (nebulaTex3,   vec2(texcoord.x + offset * 0.5, texcoord.y) * 1.8);
	vec4 secondColour = texture (nebulaTex1,   vec2(texcoord.x, texcoord.y - offset) * 1.5);
	vec4 thirdColour  = texture (nebulaTex2,   vec2(texcoord.x, texcoord.y - offset));
	
	vec4 aChanColour  = texture (alphaChanTex, vec2(texcoord.x, texcoord.y - offset));
	vec4 rampColour   = texture (rampTex,      vec2(texcoord.x, texcoord.y - offset) * 1.75); 

	// Use the greyscale value of the aChanColour as the alpha of the thirdColour.
	// This will basically set the alpha of the bright particles to a high value, and the rest to a low value
	// Hence isolating the particles from the rest of the texture values.
	
	vec4 particleColour = vec4(thirdColour.r, thirdColour.g, thirdColour.b, aChanColour.r);

	out_color = (firstColour * secondColour * 2) * particleColour * 2 * rampColour;	
}