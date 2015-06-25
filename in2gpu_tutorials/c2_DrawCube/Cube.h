#pragma once

#include <Rendering\Models\Model.h>
#include <time.h>
#include <stdarg.h>

using namespace BasicEngine::Rendering::Models;
class Cube : public Model
{
public:
	Cube();
	~Cube();

	void Create();
	virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
	virtual void Update() override final;

private:
	glm::vec3 rotation, rotation_speed;
	time_t timer;
};
