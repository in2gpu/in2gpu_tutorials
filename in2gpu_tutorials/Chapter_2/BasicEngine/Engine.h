#pragma once
#include "Core\Init\Init_GLUT.h"
#include "Managers\Scene_Manager.h"
namespace BasicEngine
{
	class Engine
	{

	public:
		Engine();
		~Engine();

		bool Init();
		void Run();

		Managers::Scene_Manager*  GetScene_Manager()  const;
		Managers::Shader_Manager* GetShader_Manager() const;
		Managers::Models_Manager* GetModels_Manager() const;

	private:
		Managers::Scene_Manager*  m_scene_manager;
		Managers::Shader_Manager* m_shader_manager;
		Managers::Models_Manager* m_models_manager;
	};
}