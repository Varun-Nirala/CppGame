#pragma once

#include <unordered_map>
#include <memory>

#include "Graphics/imageTexture.h"
#include "shaderProgram.h"

class ResourceManager
{
	using TexturePtr		= std::unique_ptr<ImageTexture>;

	using MapOfShaders		= std::unordered_map<std::string, GLuint>;
	using MapOTextures		= std::unordered_map<std::string, TexturePtr>;

public:
	bool haveTexture(const std::string& key);
	bool addTexture(const std::string key, const std::string &filepath, bool bFlipVerticallyOnLoad = false, bool bIs2D = true, GLint depth3D = 0);
	
	bool haveShader(const std::string& key);
	bool addShader(const std::string& key, const std::vector<std::pair<std::string, SHADER_TYPE>>& vec);

	const MapOfShaders& shaders() const { return m_shaders; }

	const GLuint shader(const std::string &key) const;
	GLuint shader(const std::string &key);

	const MapOTextures& textures() const { return m_textures; }

	const ImageTexture* texture(const std::string &key) const;
	ImageTexture* texture(const std::string &key);

	void print(const std::string& prefix = {}) const;

private:
	MapOfShaders	m_shaders;
	MapOTextures	m_textures;
};