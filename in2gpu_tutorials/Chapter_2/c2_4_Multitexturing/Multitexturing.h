#pragma once
#include <BasicEngine\Rendering\Models\Model.h>
#include <chrono>

using namespace BasicEngine::Rendering::Models;

typedef std::chrono::high_resolution_clock HiResTime;
typedef std::chrono::milliseconds MiliSec;
typedef std::chrono::duration<float> DeltaTime;

class Multitexturing : public Model {
public: 
	Multitexturing();
	~Multitexturing();

	void CreateSphere(float radius, unsigned int rings, unsigned int sectors);
	virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;
	virtual void Update() override final;

private:
	glm::vec3 m_Rotation, m_RotationSpeed, m_RotationSin;
};