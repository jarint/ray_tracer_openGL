#include <glad/glad.h>

#include <stdexcept>
#include <string>

#include <glm/glm.hpp>

#include "GLHandles.h"

class TextureBuffer {
  public:
    TextureBuffer(
        GLint init_interpolation = GL_LINEAR,
        GLuint init_width        = 1u,
        GLuint init_height       = 1u,
        GLuint init_n_channels   = 4u
    );

    // Because we're using the TextureHandle to do RAII for the texture for us
    // and our other types are trivial or provide their own RAII
    // we don't have to provide any specialized functions here. Rule of zero
    //
    // https://en.cppreference.com/w/cpp/language/rule_of_three
    // https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Rc-zero

    GLenum getInterpolation() const { return interpolation; }
    glm::uvec3 getDimensions() const { return glm::uvec3(width, height, n_channels); }

    void bind() { glBindTexture(GL_TEXTURE_2D, textureID); }
    void unbind() { glBindTexture(GL_TEXTURE_2D, textureID); }

    // General void ptr upload
    void uploadData(GLint new_interpolation, GLuint new_width, GLuint new_height, GLuint new_n_channels, const void *data);
    void uploadData(const void *data);

    // Pointer type to deduce n_channels (R, RG, RGB, RGBA)
    void uploadData(GLint new_interpolation, GLuint new_width, GLuint new_height, const float *data);
    void uploadData(GLint new_interpolation, GLuint new_width, GLuint new_height, const glm::vec2 *data);
    void uploadData(GLint new_interpolation, GLuint new_width, GLuint new_height, const glm::vec3 *data);
    void uploadData(GLint new_interpolation, GLuint new_width, GLuint new_height, const glm::vec4 *data);

    void uploadData(const float *data);
    void uploadData(const glm::vec2 *data);
    void uploadData(const glm::vec3 *data);
    void uploadData(const glm::vec4 *data);

  private:
    TextureHandle textureID;

    GLuint width;
    GLuint height;
    GLuint n_channels;
    GLint interpolation;

    GLint internal_format;
    GLenum format;

    void refreshFormats();
};
