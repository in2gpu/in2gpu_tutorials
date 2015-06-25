#pragma once
#include <Core\Init\Init_GLUT.h>
#include <Managers\Scene_Manager.h>
#include "Cube.h"
using namespace BasicEngine;
int main(int argc, char **argv) 
{

	BasicEngine::Core::WindowInfo window(std::string("in2gpu OpenGL Beginner Tutorial"), 400, 200, 800, 600, true);
	BasicEngine::Core::ContextInfo context(4, 5, true);
	BasicEngine::Core::FramebufferInfo frameBufferInfo(true, true, true, true);

	BasicEngine::Core::Init::Init_GLUT::Init(window, context, frameBufferInfo);

	BasicEngine::Managers::Scene_Manager* scene = new Managers::Scene_Manager();
	BasicEngine::Core::Init::Init_GLUT::SetListener(scene);

	Cube* cube = new Cube();
	cube->SetProgram(Managers::Shader_Manager::GetShader("colorShader"));
	cube->Create();

	scene->GetModels_Manager()->SetModel("cube", cube);
	

	BasicEngine::Core::Init::Init_GLUT::Run();
	
	delete scene;
	return 0;
}
