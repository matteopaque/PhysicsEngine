//
// Created by Clef on 12/15/25.
//

#ifndef OPENGLSETUP_SHADER_H
#define OPENGLSETUP_SHADER_H

#include <fstream>
#include <string>
#include <glad/glad.h>
#include <iostream>


class Shader
{
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char * fragmentPath);

    void use();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, GLfloat * value) const;
};


#endif //OPENGLSETUP_SHADER_H