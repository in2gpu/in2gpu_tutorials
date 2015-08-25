#pragma once
#include <BasicEngine\Rendering\Models\Model.h>
#include <chrono>

using namespace BasicEngine::Rendering::Models;

// Use the C++11 Chrono functionality to set up a timer
// The timer tells the frag shader how much time has passed since the app commenced
typedef std::chrono::high_resolution_clock HiResTime;	
typedef std::chrono::milliseconds MiliSec;				// require this to track ticks in miliseconds
typedef std::chrono::duration<float> DeltaTime;			// require this to convert from Chrono duration to float

class Multitexturing : public Model {
public: 
	Multitexturing();
	~Multitexturing();

	// Will generate the geometry, indices, and UVs for a sphere (same structure as the old gluSphere - "stacks and slices")
	// We could've used the cube and "morphed" it into a sphere in the vertex shader 
	// However, that is out of the scope of this tutorial
	void CreateSphere(float radius, unsigned int rings, unsigned int sectors);	

	// Drawing a static sphere. We'll let the frag shader do the UV rotation this time :)
	virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;

private:
};