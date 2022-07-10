#include "utility.h"

#include <fstream>

std::string Utility::glmVecAsString(const glm::vec2& vec, int precision)
{
	std::ostringstream str;
	str.precision(precision);
	str << std::fixed;
	str << "{ " << vec.x << ", " << vec.y << " }";
	return str.str();
}

std::string Utility::glmVecAsString(const glm::vec3& vec, int precision)
{
	std::ostringstream str;
	str.precision(precision);
	str << std::fixed;
	str << "{ " << vec.x << ", " << vec.y << ", " << vec.z << " }";
	return str.str();
}

std::string Utility::glmVecAsString(const glm::vec4& vec, int precision)
{
	std::ostringstream str;
	str.precision(precision);
	str << std::fixed;
	str << "{ " << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << " }";
	return str.str();
}

template <typename T>
void Utility::printVertexArray(const T* arr, size_t size, int vpv, const char* prefix, const char* msg)
{
	using ns_Util::Logger;
	if (msg)
	{
		if (prefix)
		{
			Logger::LOG_MSG(prefix);
		}
		Logger::LOG_MSG(msg);
	}

	if (prefix)
	{
		Logger::LOG_MSG(prefix);
	}
	
	Logger::LOG_MSG("{ ");
	for (size_t i = 0; i < size; ++i)
	{
		if (i > 0 && i % vpv == 0)
		{
			Logger::LOG_MSG("}\n", prefix, "{ ");
		}
		Logger::LOG_MSG(arr[i], ", ");
	}
	Logger::LOG_MSG("}\n");
}
