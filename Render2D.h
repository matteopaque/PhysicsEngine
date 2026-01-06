//
// Created by Clef on 1/6/26.
//

#ifndef OPENGLSETUP_RENDER2D_H
#define OPENGLSETUP_RENDER2D_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include "Texture.h"

class Render2D
{
    unsigned int VBO;
    unsigned int VAO;
    Texture texture;
public:
    // use points in viewport space 800x600
    void Initialize(std::vector<glm::vec2> points);
    void InitializeSquare(glm::vec2 center, float semiWidth);
    void use();

};


#endif //OPENGLSETUP_RENDER2D_H