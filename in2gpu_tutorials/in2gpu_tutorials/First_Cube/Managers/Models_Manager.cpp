#include "Models_Manager.h"

using namespace Managers;
using namespace Rendering;

Models_Manager::Models_Manager()
{
	
	Models::Triangle* triangle = new Models::Triangle();
	triangle->SetProgram(Shader_Manager::GetShader("colorShader"));
	triangle->Create();
	gameModelList_NDC["triangle"] = triangle;

	Models::Quad* quad = new Models::Quad();
	quad->SetProgram(Shader_Manager::GetShader("colorShader"));
	quad->Create();
	gameModelList_NDC["quad"] = quad;

	Models::Cube* cube = new Models::Cube();
	cube->SetProgram(Shader_Manager::GetShader("colorShader"));
	cube->Create();
	gameModelList["cube"] = cube;

}

Models_Manager::~Models_Manager()
{

	for (auto model: gameModelList)
	{
		delete model.second;
	}
	gameModelList.clear();

	for (auto model : gameModelList_NDC)
	{
		delete model.second;
	}
	gameModelList_NDC.clear();
}



void Models_Manager::Update()
{
	for (auto model: gameModelList)
	{
		model.second->Update();
	}
	for (auto model : gameModelList_NDC)
	{
		model.second->Update();
	}
}

//NDC
void Models_Manager::Draw()
{
	for (auto model : gameModelList_NDC)
	{
		model.second->Draw();
	}
}

void Models_Manager::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	for (auto model : gameModelList)
	{
		model.second->Draw(projection_matrix, view_matrix);
	}
}

void Models_Manager::DeleteModel(const std::string& gameModelName)
{

	IGameObject* model = gameModelList[gameModelName];
	model->Destroy();
	gameModelList.erase(gameModelName);

}

void Models_Manager::DeleteModel_NDC(const std::string& gameModelName)
{

	IGameObject* model = gameModelList_NDC[gameModelName];
	model->Destroy();
	gameModelList_NDC.erase(gameModelName);

}

const IGameObject& Models_Manager::GetModel(const std::string& gameModelName) const
{
	return (*gameModelList.at(gameModelName));
}

const IGameObject& Models_Manager::GetModel_NDC(const std::string& gameModelName) const
{
	return (*gameModelList_NDC.at(gameModelName));
}
