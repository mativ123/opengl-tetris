#pragma once

#include "include/glad/glad.h"
#include "include/stb/stb_image.h"

#include "shader.h"

class Texture
{
    public:
        GLuint ID;
        GLenum type;
        Texture(const char *image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

        void texUnit(Shader &shader, const char *uniform, GLuint unit);
        void Bind();
        void Unbind();
        void Delete();
};
