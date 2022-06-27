#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include "logger.h"

template <typename T>
static void SAFE_RELEASE(T* &refToPtr)
{
	if (refToPtr)
	{
		refToPtr->release();
		delete refToPtr;
		refToPtr = nullptr;
	}
}

inline std::string glmVecAsString(const glm::vec2& vec, int precision = 2)
{
	std::ostringstream str;
	str.precision(precision);
	str << std::fixed;
	str << "{ " << vec.x << ", " << vec.y << " }";
	return str.str();
}

inline std::string glmVecAsString(const glm::vec3& vec, int precision = 2)
{
	std::ostringstream str;
	str.precision(precision);
	str << std::fixed;
	str << "{ " << vec.x << ", " << vec.y << ", " << vec.z << " }";
	return str.str();
}

inline std::string glmVecAsString(const glm::vec4& vec, int precision = 2)
{
	std::ostringstream str;
	str.precision(precision);
	str << std::fixed;
	str << "{ " << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << " }";
	return str.str();
}

template <typename T>
static void printArray(const T* arr, size_t size, const char* prefix = nullptr, const char *msg = nullptr)
{
	if (msg)
	{
		ns_Util::Logger::LOG_MSG(msg);
	}

	if (prefix)
	{
		ns_Util::Logger::LOG_MSG(prefix);
	}
	for (size_t i = 0; i < size; ++i)
	{
		ns_Util::Logger::LOG_MSG(arr[i], ", ");
	}
	ns_Util::Logger::LOG_MSG('\n');
}

template <typename T>
static void printArrObject(const T* arr, size_t size, const char* prefix = nullptr, const char* msg = nullptr, const char* objTitle = nullptr)
{
	if (msg)
	{
		ns_Util::Logger::LOG_MSG(msg);
	}
	std::string s(prefix);
	s += "    ";
	for (size_t i = 0; i < size; ++i)
	{
		ns_Util::Logger::LOG_MSG(prefix, objTitle, i + 1, ":\n");
		arr[i]->print(s.c_str());
		ns_Util::Logger::LOG_MSG('\n');
	}
}

template <typename T>
static void printVertexArray(const T* arr, size_t size, int vpv, const char* prefix = nullptr, const char* msg = nullptr)
{
	if (msg)
	{
		if (prefix)
		{
			ns_Util::Logger::LOG_MSG(prefix);
		}
		ns_Util::Logger::LOG_MSG(msg);
	}

	if (prefix)
	{
		ns_Util::Logger::LOG_MSG(prefix);
	}
	ns_Util::Logger::LOG_MSG("{ ");
	for (size_t i = 0; i < size; ++i)
	{
		if (i > 0 && i % vpv == 0)
		{
			ns_Util::Logger::LOG_MSG("}\n", prefix, "{ ");
		}
		ns_Util::Logger::LOG_MSG(arr[i], ", ");
	}
	ns_Util::Logger::LOG_MSG("}\n");
}
