#pragma once
#include <BasicEngine\Engine.h>
#include "CubeIndex.h"

using namespace BasicEngine;
int main(int argc, char **argv)
{

	Engine* engine = new Engine();
	engine->Init();

	engine->GetShader_Manager()->CreateProgram("cubeShader",
											   "Shaders\\Cube_Vertex_Shader.glsl",
											   "Shaders\\Cube_Fragment_Shader.glsl");

	CubeIndex* cube = new CubeIndex();
	cube->SetProgram(engine->GetShader_Manager()->GetShader("cubeShader"));
	cube->Create();

	engine->GetModels_Manager()->SetModel("cube", cube);

	glDisable(GL_CULL_FACE);

	engine->Run();

	delete engine;
	return 0;
}
