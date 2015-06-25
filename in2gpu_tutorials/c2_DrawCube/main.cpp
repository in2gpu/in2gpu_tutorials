#pragma once
#include <Core\Init\Init_GLUT.h>
#include <Managers\Scene_Manager.h>
#include "Cube.h"
using namespace Core;
using namespace Init;
int main(int argc, char **argv) 
{

	WindowInfo window(std::string("in2gpu OpenGL Beginner Tutorial"), 400, 200, 800, 600, true);
	ContextInfo context(4, 5, true);
	FramebufferInfo frameBufferInfo(true, true, true, true);

	Init_GLUT::Init(window, context, frameBufferInfo);

	Managers::Scene_Manager* scene = new Managers::Scene_Manager();
	Init_GLUT::SetListener(scene);

	Rendering::Models::Cube* cube = new Rendering::Models::Cube();
	cube->SetProgram(Managers::Shader_Manager::GetShader("colorShader"));
	cube->Create();

	scene->GetModels_Manager()->SetModel("cube", cube);
	

	Init_GLUT::Run();
	
	delete scene;
	return 0;
}
