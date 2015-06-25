#pragma once
#include "Shader_Manager.h"
#include "Models_Manager.h"
#include "../Core/Init/IListener.h"
namespace Managers
{
	class Scene_Manager : public Core::IListener

	{
	public:
		Scene_Manager();
		~Scene_Manager();

		virtual void NotifyBeginFrame();
		virtual void NotifyDisplayFrame();
		virtual void NotifyEndFrame();
		virtual void NotifyReshape(int width, int height, int previos_width, int previous_height);

		Managers::Models_Manager* GetModels_Manager();
		
	private:
		Managers::Shader_Manager* shader_manager;
		Managers::Models_Manager* models_manager;
		glm::mat4 projection_matrix;
		glm::mat4 view_matrix;
	};

}