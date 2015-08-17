#pragma once
#include <BasicEngine\Rendering\Models\Model.h>
#include <time.h>

using namespace BasicEngine::Rendering::Models;

class Multitexturing : public Model {
public: 
	Multitexturing();
	~Multitexturing();

	void         Create();
	virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
	virtual void Update() override final;

private:
	glm::vec3 m_Rotation, m_RotationSpeed;
	glm::vec3 m_RotationSin;
	time_t    m_Timer;
};