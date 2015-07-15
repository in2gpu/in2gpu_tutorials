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
			glm::vec2 texture;

			VertexFormat(const glm::vec3 &iPos, const glm::vec4 &iColor)
			{
				position = iPos;
				color = iColor;
				texture.x = texture.y = 0;
			}
			VertexFormat(const glm::vec3 &iPos, const glm::vec2 &iTexture)
			{
				position = iPos;
				texture = iTexture;
				color.r = color.g = color.b = color.a = 0;
			}

			VertexFormat()
			{

			}

		};
	}
}
