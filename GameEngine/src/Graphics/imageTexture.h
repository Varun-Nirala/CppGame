#pragma once

#include <glad/glad.h>
#include <vector>
#include <string>

#define GLM_FORCE_SILENT_WARNINGS       // to silent warnings
#include <glm/glm.hpp>

class ImageTexture
{
	using value_type = GLfloat;
public:
	~ImageTexture() { release(); }
	explicit ImageTexture(GLenum target = GL_TEXTURE_2D) : m_target(target) { glGenTextures(1, &m_id); }

	void setTarget(GLenum target);
	bool is1D() const { return m_target == GL_TEXTURE_1D; }
	bool is2D() const { return m_target == GL_TEXTURE_2D; }
	bool is3D() const { return m_target == GL_TEXTURE_3D; }

	bool isActive() const { return m_bActive; }

	void activate() { m_bActive = true; }
	void deactivate() { m_bActive = false; }

	GLuint id() const { return m_id; }

	void setCoordinates(std::initializer_list<value_type> iList);
	void setCoordinates(const std::vector<value_type>& iList);
	void setCoordinates(const value_type* iList);

	const value_type* coordinates() const { return m_coordinates.data(); }
	value_type* coordinates() { return m_coordinates.data(); }

	GLsizei coordinatesCount() const { return (GLsizei)m_coordinates.size() / m_valuePerCoordinate; }
	void setValuePerCoordinate(GLsizei val) { m_valuePerCoordinate = val; }
	GLsizei valuePerCoordinate() const { return m_valuePerCoordinate; }

	GLsizei coordinateSize() const { return coordinatesCount() * valuePerCoordinate(); }

	// GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER
	void setWrapping_S(GLint param);
	void setWrapping_T(GLint param);
	void setWrapping_R(GLint param);
	void setWrapping(GLint param);

	void setBorderColor(value_type r, value_type g, value_type b, value_type a);
	void setBorderColor(glm::vec4 color);

	// For both min and mag GL_LINEAR, GL_NEAREST
	// Only for min -> GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR
	void setFilter_minification(GLint param) { glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, param); }
	void setFilter_magnification(GLint param) { glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, param); }
	void setFilter(GLint param);

	void generateMipMap() { glGenerateMipmap(m_target); }

	void bind() const { glBindTexture(m_target, m_id); }
	void unbind() const { glBindTexture(m_target, 0); }

	bool generateTextureImage(const std::string& filepath, bool bFlipVerticallyOnLoad, GLenum pixelDataType, GLsizei depth3D = 0);

	void release();

	void print(const std::string& prefix = {}) const;

private:
	bool loadTextureImage(const std::string& filepath, bool bFlipVerticallyOnLoad, unsigned char* imgData, int& width, int& height, int& numOfChannels);

private:
	GLuint					m_id{};
	std::vector<value_type>	m_coordinates;
	GLsizei					m_valuePerCoordinate{};
	glm::vec4				m_borderColor{};
	GLenum					m_target{ GL_TEXTURE_2D };
	bool					m_bActive{ false };
};