#ifndef __COMMON_H__
#define __COMMON_H__

#include <GLFW\glfw3.h>
#include "Maths\Vector3.h"

namespace nsEngine {
	namespace nsCommon
	{
		const double gGRAVITY = -10;

		const nsMaths::Vector3 gFRICTION(0.8, 1, 1);

		const double gPIXEL_PER_SECOND = 5;
		const double gFPS = 60 * gPIXEL_PER_SECOND;

		inline double getElapsedTime()
		{
			static double lastTime = 0;
			double dt = glfwGetTime() - lastTime;
			lastTime = glfwGetTime();
			return dt;
		}
	}
}
#endif