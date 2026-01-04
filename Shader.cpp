//
// Created by Clef on 12/15/25.
//

#include "Shader.h"

std::string readFile (const std::string& path)
{
    std::ifstream ifs {};
    ifs.open(path);
    std::string content (
        (std::istreambuf_iterator<char>(ifs)),
            (std::istreambuf_iterator<char>())
        );
    return content;
}


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{

    const std::string vertexShaderString = readFile(vertexPath);
    const char * vertexShaderSource = vertexShaderString.c_str();

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog [512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std:: cout << "vertex shader fucked\n" << infoLog << "\n";
    }

    std::string fragmentShaderString = readFile(fragmentPath);
    const char * fragmentShaderSource = fragmentShaderString.c_str();

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "fragment shader fucked\n" << infoLog << "\n";
    }



    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cout << "shaders program's fucked\n" << infoLog << "\n";
    }
    glDeleteShader (vertexShader);
    glDeleteShader (fragmentShader);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, GLfloat* value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value);
}



