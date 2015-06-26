#pragma once
#include <BasicEngine\Engine.h>
#include "Cube.h"

using namespace BasicEngine;
int main(int argc, char **argv) 
{

	Engine* engine = new Engine();
	engine->Init();

	engine->GetShader_Manager()->CreateProgram("cubeShader",
											   "Shaders\\Cube_Vertex_Shader.glsl",
											   "Shaders\\Cube_Fragment_Shader.glsl");

	Cube* cube = new Cube();
	cube->SetProgram(engine->GetShader_Manager()->GetShader("cubeShader"));
	cube->Create();

	engine->GetModels_Manager()->SetModel("cube", cube);
	
	engine->Run();
		
	delete engine;
	return 0;
}
