#include "resourceManager.h"
#include "Common/logger.h"

bool ResourceManager::haveTexture(const std::string& key)
{
    return m_textures.count(key) != 0;
}

bool ResourceManager::addTexture(const std::string key, const std::string& filepath, bool bFlipVerticallyOnLoad, bool bIs2D, GLint depth3D)
{
    TexturePtr pTexture = std::make_unique<ImageTexture>(bIs2D ? GL_TEXTURE_2D : GL_TEXTURE_3D);

    if (!pTexture->generateTextureImage(filepath, bFlipVerticallyOnLoad, GL_UNSIGNED_BYTE, depth3D))
    {
        ns_Util::Logger::LOG_ERROR("Failed to generate texture : ", filepath, '\n');
        assert(false);
        return false;
    }

    pTexture->bind();

    pTexture->setBorderColor(1.0f, 1.0f, 1.0f, 1.0f);
    pTexture->setWrapping_S(GL_CLAMP_TO_EDGE);
    pTexture->setWrapping_T(GL_CLAMP_TO_BORDER);
    pTexture->setWrapping_R(GL_CLAMP_TO_EDGE);
    pTexture->setFilter_minification(GL_LINEAR_MIPMAP_LINEAR);
    pTexture->setFilter_magnification(GL_LINEAR);

    pTexture->generateMipMap();
    pTexture->unbind();

    return m_textures.insert(std::make_pair(key, std::move(pTexture))).second;
}

bool ResourceManager::haveShader(const std::string& key)
{
    return m_shaders.count(key) != 0;
}

bool ResourceManager::addShader(const std::string& key, const std::vector<std::pair<std::string, SHADER_TYPE>>& vec)
{
    GLuint shaderProgramID = ShaderProgram::createShader();

    for (size_t i = 0, size = vec.size(); i < size; ++i)
    {
        if (!ShaderProgram::attachShader(vec[i].first, vec[i].second, shaderProgramID))
        {
            ns_Util::Logger::LOG_ERROR("Failed to compile shader : ", vec[i].first, '\n');
            assert(false);
            return false;
        }
    }

    if (!ShaderProgram::linkShader(shaderProgramID))
    {
        ns_Util::Logger::LOG_ERROR("Failed to link shader : ", shaderProgramID, '\n');
        assert(false);
        return false;
    }

    return m_shaders.insert(std::make_pair(key, shaderProgramID)).second;
}

const GLuint ResourceManager::shader(const std::string& key) const
{
	return (m_shaders.count(key) == 0) ? 0 : m_shaders.at(key);
}

GLuint ResourceManager::shader(const std::string& key)
{
	return (m_shaders.count(key) == 0) ? 0 : m_shaders[key];
}

const ImageTexture* ResourceManager::texture(const std::string& key) const
{
	return (m_textures.count(key) == 0) ? nullptr : m_textures.at(key).get();
}

ImageTexture* ResourceManager::texture(const std::string& key)
{
	return (m_textures.count(key) == 0) ? nullptr : m_textures[key].get();
}

void ResourceManager::print(const std::string& prefix) const
{
    using ns_Util::Logger;
    Logger::LOG_MSG(prefix, "ResourceManager\n");

    if (m_textures.empty())
    {
        Logger::LOG_MSG(prefix, "  Textures          : Empty\n\n");
    }
    else
    {
        Logger::LOG_MSG(prefix, "  Textures          : ", m_textures.size(), "\n\n");
        int i = 1;
        for (auto& p : m_textures)
        {
            Logger::LOG_MSG(prefix, "  Textures # ", i++, '\n');
            p.second->print(prefix + "  ");
        }
    }
    
    if (m_shaders.empty())
    {
        Logger::LOG_MSG(prefix, "  Shaders           : Empty\n\n");
    }
    else
    {
        Logger::LOG_MSG(prefix, "  Shaders           : ", m_shaders.size(), "\n\n");
        int i = 1;
        for (auto& p : m_shaders)
        {
            Logger::LOG_MSG(prefix, "  Shaders # ", i++, "Key : ", p.first, ", ID : ", p.second, '\n');
        }
    }
    Logger::LOG_MSG('\n');
}