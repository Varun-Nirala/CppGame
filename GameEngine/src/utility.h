#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include "Common/logger.h"

class Utility
{
public:
	static std::string glmVecAsString(const glm::vec2& vec, int precision = 2);
	static std::string glmVecAsString(const glm::vec3& vec, int precision = 2);
	static std::string glmVecAsString(const glm::vec4& vec, int precision = 2);

	template <typename T>
	static void printVertexArray(const T* arr, size_t size, int vpv, const char* prefix = nullptr, const char* msg = nullptr);
};