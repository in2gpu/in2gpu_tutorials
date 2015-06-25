#pragma once
#include <iostream>
#include <glew\glew.h>
#include <freeglut\freeglut.h>
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