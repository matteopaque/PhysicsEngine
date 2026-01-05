//
// Created by Clef on 1/5/26.
//

#ifndef OPENGLSETUP_LINERENDER_H
#define OPENGLSETUP_LINERENDER_H
#include <glm/vec3.hpp>

#include "glad/glad.h"


class LineVertexLoader
{
    unsigned int VBO;
    unsigned int VAO;
public:
    void Initialize(glm::vec3 point1, glm::vec3 point2);
    void newLine(glm::vec3 point1, glm::vec3 point2);
    void useVertexArray();
};


#endif //OPENGLSETUP_LINERENDER_H