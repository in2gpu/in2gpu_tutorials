#pragma once
#include <glm\glm.hpp>
namespace BasicEngine
{
	namespace Rendering
	{
		struct VertexFormat
		{

			glm::vec3 position;
			glm::vec4 color;

			VertexFormat(const glm::vec3 &iPos, const glm::vec4 &iColor)
			{
				position = iPos;
				color = iColor;
			}
			VertexFormat()
			{

			}

		};
	}
}
