#include "imageTexture.h"

#include "stb_image.h"
#include <glm/gtc/type_ptr.hpp>

#include "Common/logger.h"

void ImageTexture::setTarget(GLenum target)
{
    if (target == GL_TEXTURE_1D || target == GL_TEXTURE_2D || target == GL_TEXTURE_3D)
    {
        m_target = target;
        return;
    }
    ns_Util::Logger::LOG_ERROR("Target not supported. Supported targets are (GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D)\n");
}

void ImageTexture::setCoordinates(std::initializer_list<value_type> iList)
{
    m_coordinates.resize(coordinateSize());
    std::copy(iList.begin(), iList.end(), m_coordinates.begin());
}

void ImageTexture::setCoordinates(const std::vector<value_type>& iList)
{
    m_coordinates.resize(coordinateSize());
    std::copy(iList.begin(), iList.end(), m_coordinates.begin());
}

void ImageTexture::setCoordinates(const value_type* iList)
{
    m_coordinates.resize(coordinateSize());
    for (size_t i = 0, size = m_coordinates.size(); i < size; ++i)
    {
        m_coordinates[i] = iList[i];
    }
}

void ImageTexture::setWrapping_S(GLint param)
{
    glTexParameteri(m_target, GL_TEXTURE_WRAP_S, param);
}

void ImageTexture::setWrapping_T(GLint param)
{
    if (is2D() || is3D())
    {
        glTexParameteri(m_target, GL_TEXTURE_WRAP_T, param);
    }
}

void ImageTexture::setWrapping_R(GLint param)
{
    if (is3D())
    {
        glTexParameteri(m_target, GL_TEXTURE_WRAP_R, param);
    }
}

void ImageTexture::setWrapping(GLint param)
{
    setWrapping_S(param);
    setWrapping_T(param);
    setWrapping_R(param);
}

void ImageTexture::setBorderColor(value_type r, value_type g, value_type b, value_type a)
{
    m_borderColor.r = r;
    m_borderColor.g = g;
    m_borderColor.b = b;
    m_borderColor.a = a;
    glTexParameterfv(m_target, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(m_borderColor));
}

void ImageTexture::setBorderColor(glm::vec4 color)
{
    m_borderColor = color;
    glTexParameterfv(m_target, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(m_borderColor));
}

void ImageTexture::setFilter(GLint param)
{
    setFilter_minification(param);
    setFilter_magnification(param);
}

bool ImageTexture::generateTextureImage(const std::string& filepath, bool bFlipVerticallyOnLoad, GLenum pixelDataType, GLsizei depth3D)
{
    unsigned char* imgData{};
    int	width{};
    int	height{};
    int	numOfChannels{};

    if (!loadTextureImage(filepath, bFlipVerticallyOnLoad, imgData, width, height, numOfChannels))
    {
        ns_Util::Logger::LOG_ERROR("Loading image failed : ", filepath, '\n');
        assert(false);
        return false;
    }

    GLint requiredColorFormat = numOfChannels == 3 ? GL_RGB : GL_RGBA;
    GLenum srcColorFormat = numOfChannels == 3 ? GL_RGB : GL_RGBA;

    if (is2D())
    {
        glTexImage2D(
            GL_TEXTURE_2D,              // texture target
            0,                          // mipmap level, default value is 0
            requiredColorFormat,        // format in which we want to store the data
            width,                      // width of resulting texture we want
            height,                     // height of resulting texture we want
            0,                          // legacy, always 0 (border)
            srcColorFormat,             // src - format of image
            pixelDataType,              // src - data type of image
            imgData                     // src - image data
        );

        stbi_image_free(imgData);
    }
    else if (is3D())
    {
        glTexImage3D(
            GL_TEXTURE_3D,              // texture target
            0,                          // mipmap level, default value is 0
            requiredColorFormat,        // format in which we want to store the data
            width,                      // width of resulting texture we want
            height,                     // height of resulting texture we want
            depth3D,                    // depth of the image or number of layer in texture array (all support atleast 256 texel deep)
            0,                          // legacy, always 0 (border)
            srcColorFormat,             // src - format of image
            pixelDataType,              // src - data type of image
            imgData                     // src - image data
        );

        stbi_image_free(imgData);
    }
    else
    {
        return false;
    }

    return true;
}

void ImageTexture::release()
{
    glDeleteTextures(1, &m_id);
    m_coordinates.clear();
}

void ImageTexture::print(const std::string& prefix) const
{
    using ns_Util::Logger;
    Logger::LOG_MSG(prefix, "Texture\n");
    Logger::LOG_MSG(prefix, "  ID              : ", m_id, '\n');
    Logger::LOG_MSG(prefix, "  Target          : ", is1D() ? "GL_TEXTURE_1D" : (is2D() ? "GL_TEXTURE_2D" : "GL_TEXTURE_3D"), '\n');
    Logger::LOG_MSG(prefix, "  Active          : ", m_bActive ? "True" : "False", '\n');
    Logger::LOG_MSG(prefix, "  Value per coord : ", m_valuePerCoordinate, '\n');
    Logger::LOG_MSG(prefix, "  Border color    : { ", m_borderColor.r, ',', m_borderColor.g, ',', m_borderColor.b, ',', m_borderColor.a, " }\n");

    if (m_coordinates.empty())
    {
        ns_Util::Logger::LOG_MSG(prefix, "  Coordinates     : Empty", '\n');
    }
    else
    {
        ns_Util::Logger::LOG_MSG(prefix, "  Coordinate count : ", m_coordinates.size(), '\n');
        ns_Util::Logger::LOG_MSG(prefix, "  Coordinates :\n");
        //printVertexArray(m_coordinates.data(), m_coordinates.size(), (int)m_valuePerCoordinate, (prefix + "    ").c_str());
    }
    ns_Util::Logger::LOG_MSG('\n');
}

bool ImageTexture::loadTextureImage(const std::string& filepath, bool bFlipVerticallyOnLoad, unsigned char *imgData, int &width, int &height, int &numOfChannels)
{
    imgData = nullptr;
    width = height = numOfChannels = 0;

    stbi_set_flip_vertically_on_load(bFlipVerticallyOnLoad);

    imgData = stbi_load(filepath.c_str(), &width, &height, &numOfChannels, 0);

    if (!imgData)
    {
        ns_Util::Logger::LOG_ERROR("Unable to load image : ", filepath, '\n');
        assert(false);
        return false;
    }

    return true;
}