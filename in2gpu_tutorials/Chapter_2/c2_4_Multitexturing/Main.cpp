#pragma once
#include <BasicEngine\Engine.h>
#include "Multitexturing.h"
#include "soil\SOIL.h"							//new

using namespace BasicEngine;

int main(int argc, char **argv) {
	Engine* engine = new Engine();
	engine->Init();

	engine->GetShader_Manager()->CreateProgram("cubeShader",
		"Shaders\\Cube_Vertex_Shader.glsl",
		"Shaders\\Cube_Fragment_Shader.glsl");

	Multitexturing* multitexSphere = new Multitexturing();
	int program = engine->GetShader_Manager()->GetShader("cubeShader");
	if (program != 0) {
		multitexSphere->SetProgram(program);
		multitexSphere->CreateSphere(2, 24, 48);
	}
	else {
		std::cout << "invalid program...";
		std::cin.get();
	}

	//new
	multitexSphere->SetTexture("BaseTexture", SOIL_load_OGL_texture("Textures\\nebula1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS));
	multitexSphere->SetTexture("SecondTexture", SOIL_load_OGL_texture("Textures\\nebula2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS));
	multitexSphere->SetTexture("AlphaChanTexture", SOIL_load_OGL_texture("Textures\\alphaChan.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS));
	multitexSphere->SetTexture("RampTexture", SOIL_load_OGL_texture("Textures\\ramp.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS));

	engine->GetModels_Manager()->SetModel("cube", multitexSphere);

	engine->Run();

	delete engine;
	return 0;
}
