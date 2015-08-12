#pragma once

#include <BasicEngine\Rendering\Models\Model.h>
#include <time.h>
#include <stdarg.h>

using namespace BasicEngine::Rendering::Models;

class CubeTextureAdvanced : public Model
{
public:
	CubeTextureAdvanced();
	~CubeTextureAdvanced();

	void Create();
	virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
	virtual void Update() override final;

private:
	glm::vec3 rotation, rotation_speed;
	glm::vec3 rotation_sin;
	time_t timer;
};
