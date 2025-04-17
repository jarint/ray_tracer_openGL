#include "TextureBuffer.h"

#include <vector>

// --------------------------------------------------------------------------

TextureBuffer::TextureBuffer(GLint init_interpolation, GLuint init_width, GLuint init_height, GLuint init_n_channels)
    : textureID()
    , interpolation(init_interpolation)
    , width(init_width)
    , height(init_height)
    , n_channels(init_n_channels)
    , internal_format()
    , format()
{
    refreshFormats();

    // Fill data with default values
    switch (n_channels) {
        case 4u: {
            std::vector<glm::vec4> data(width * height, glm::vec4(0.f, 0.f, 0.f, 1.f));
            uploadData(data.data());
        } break;
        case 3u: {
            std::vector<glm::vec3> data(width * height, glm::vec3(0.f, 0.f, 0.f));
            uploadData(data.data());
        } break;
        case 2u: {
            std::vector<glm::vec2> data(width * height, glm::vec2(0.f, 0.f));
            uploadData(data.data());
        } break;
        case 1u: {
            std::vector<float> data(width * height, 0.f);
            uploadData(data.data());
        } break;
        default: throw std::runtime_error("Invalid component count (1,2,3,4 only)");
    }
}

void TextureBuffer::uploadData(
    GLint new_interpolation,
    GLuint new_width,
    GLuint new_height,
    GLuint new_n_channels,
    const void *data
)
{
    interpolation = new_interpolation;
    width         = new_width;
    height        = new_height;
    n_channels    = new_n_channels;
    refreshFormats();

    uploadData(data);
}

void TextureBuffer::uploadData(const void *data)
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // Abstract alignment
    bind();

    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_FLOAT, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, interpolation);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, interpolation);

    unbind();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);  // Return to default alignment
}

void TextureBuffer::uploadData(GLint new_interpolation, GLuint new_width, GLuint new_height, const float *data)
{
    uploadData(new_interpolation, new_width, new_height, 1, data);
}

void TextureBuffer::uploadData(GLint new_interpolation, GLuint new_width, GLuint new_height, const glm::vec2 *data)
{
    uploadData(new_interpolation, new_width, new_height, 2, data);
}

void TextureBuffer::uploadData(GLint new_interpolation, GLuint new_width, GLuint new_height, const glm::vec3 *data)
{
    uploadData(new_interpolation, new_width, new_height, 3, data);
}

void TextureBuffer::uploadData(GLint new_interpolation, GLuint new_width, GLuint new_height, const glm::vec4 *data)
{
    uploadData(new_interpolation, new_width, new_height, 4, data);
}

void TextureBuffer::uploadData(const float *data) { uploadData(interpolation, width, height, 1, data); }
void TextureBuffer::uploadData(const glm::vec2 *data) { uploadData(interpolation, width, height, 2, data); }
void TextureBuffer::uploadData(const glm::vec3 *data) { uploadData(interpolation, width, height, 3, data); }
void TextureBuffer::uploadData(const glm::vec4 *data) { uploadData(interpolation, width, height, 4, data); }

void TextureBuffer::refreshFormats()
{
    switch (n_channels) {
        case 4u: internal_format = GL_RGBA32F; break;
        case 3u: internal_format = GL_RGB32F; break;
        case 2u: internal_format = GL_RG32F; break;
        case 1u: internal_format = GL_R32F; break;
        default: throw std::runtime_error("Invalid component count (1,2,3,4 only)");
    }

    switch (n_channels) {
        case 4u: format = GL_RGBA; break;
        case 3u: format = GL_RGB; break;
        case 2u: format = GL_RG; break;
        case 1u: format = GL_RED; break;
        default: throw std::runtime_error("Invalid component count (1,2,3,4 only)");
    }
}
