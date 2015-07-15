#pragma once
#include <BasicEngine\Engine.h>
#include "CubeTexture.h"

using namespace BasicEngine;
int main(int argc, char **argv)
{

	Engine* engine = new Engine();
	engine->Init();

	engine->GetShader_Manager()->CreateProgram("cubeShader",
											   "Shaders\\Cube_Vertex_Shader.glsl",
											   "Shaders\\Cube_Fragment_Shader.glsl");

	CubeTexture* cube = new CubeTexture();
	int program = engine->GetShader_Manager()->GetShader("cubeShader");
	if (program != 0)
	{
		cube->SetProgram(program);
		cube->Create();
	}
	else
	{
		std::cout << "invalid program...";
		std::cin.get();
	}
	unsigned int texture = engine->GetTexture_Loader()->LoadTexture("Textures\\Crate.bmp", 256, 256);
	cube->SetTexture("Create",texture);

	engine->GetModels_Manager()->SetModel("cube", cube);

	engine->Run();

	delete engine;
	return 0;
}
