//
// Created by Clef on 1/5/26.
//

#include "LineVertexLoader.h"
#include <GLFW/glfw3.h>

void LineVertexLoader::Initialize(glm::vec3 point1, glm::vec3 point2)
{
    if (initialized)
    {
        newLine(point1, point2);
        return;
    }
    std::vector<float> data {
        point1.x, point1.y, point1.z,
        point2.x, point2.y, point2.z
    };
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);


    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6, data.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    initialized = true;
}
void LineVertexLoader::Initialize(Line line)
{
    Initialize(line.p1, line.p2);
}
void LineVertexLoader::newLine(Line& line)
{
    newLine(line.p1, line.p2);
}
LineVertexLoader::LineVertexLoader( const Line& line)
{
    Initialize(line);
}




void LineVertexLoader::newLine(glm::vec3 point1, glm::vec3 point2)
{
    std::vector<float> data {
        point1.x, point1.y, point1.z,
        point2.x, point2.y, point2.z
    };

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 6*sizeof(float), data.data());

}


void LineVertexLoader::useVertexArray()
{
    glBindVertexArray(VAO);
}

