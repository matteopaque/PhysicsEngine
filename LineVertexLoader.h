//
// Created by Clef on 1/5/26.
//

#ifndef OPENGLSETUP_LINERENDER_H
#define OPENGLSETUP_LINERENDER_H
#include <glm/vec3.hpp>

#include "glad/glad.h"
#include "Line.h"


class LineVertexLoader
{
    unsigned int VBO = 0;
    unsigned int VAO = 0;
    bool initialized = false;
public:
    LineVertexLoader(Line &line);
    LineVertexLoader(){};
    void Initialize(glm::vec3 point1, glm::vec3 point2);
    void Initialize(Line line);
    void newLine(glm::vec3 point1, glm::vec3 point2);
    void newLine(Line & line);
    void useVertexArray();
};


#endif //OPENGLSETUP_LINERENDER_H