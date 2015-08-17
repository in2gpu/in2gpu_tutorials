#pragma once
#include <BasicEngine\Engine.h>
#include "CubeTextureAdvanced.h"
#include "soil\SOIL.h"							//new

using namespace BasicEngine;

int main(int argc, char **argv) {
	Engine* engine = new Engine();
	engine->Init();

	engine->GetShader_Manager()->CreateProgram("cubeShader",
		"Shaders\\Cube_Vertex_Shader.glsl",
		"Shaders\\Cube_Fragment_Shader.glsl");

	CubeTextureAdvanced* cube = new CubeTextureAdvanced();
	int program = engine->GetShader_Manager()->GetShader("cubeShader");
	if (program != 0) {
		cube->SetProgram(program);
		cube->Create();
	}
	else {
		std::cout << "invalid program...";
		std::cin.get();
	}

	//new
	cube->SetTexture("Create", SOIL_load_OGL_texture("Textures\\Crate.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	engine->GetModels_Manager()->SetModel("cube", cube);

	engine->Run();

	delete engine;
	return 0;
}
