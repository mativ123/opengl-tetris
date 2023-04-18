#pragma once

#include "include/glad/glad.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
    public:
        unsigned int ID;

        Shader(const char *vertexPath, const char *fragmentPath);
        void use();
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setMat4f(const std::string &name, GLsizei n, const GLfloat* value) const;
        void setVec4f(const std::string &name, const GLfloat *value) const;
        void setVec4f(const std::string &name, GLsizei n, const GLfloat *value) const;
};
