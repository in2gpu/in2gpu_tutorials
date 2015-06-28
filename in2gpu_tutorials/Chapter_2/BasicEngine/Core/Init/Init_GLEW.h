#pragma once
#include <iostream>
#include <glew\glew.h>
#include <freeglut\freeglut.h>
namespace BasicEngine
{
	namespace Core
	{
		namespace Init
		{
			class Init_GLEW
			{
			public:
				Init_GLEW();
				~Init_GLEW();

				static void Init();
			};
		}
	}
}