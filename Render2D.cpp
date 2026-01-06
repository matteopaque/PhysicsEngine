//
// Created by Clef on 1/6/26.
//

#include "Render2D.h"


void Render2D::Initialize(std::vector<glm::vec2> points)
{
    std::vector<float> data;
    for (auto & point : points)
    {
        data.push_back(point.x);
        data.push_back(point.y);
        data.push_back(0);
    }
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);


    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*data.size(), data.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Render2D::InitializeSquare(glm::vec2 center, float semiWidth)
{
    std::vector<glm::vec2> squarePattern{
        {1.f, 1.f},
        {1.f, -1.f},
        {-1.f, -1.f},
        {-1.f, 1.f},
        {1.f, 1.f},
        {-1.f, -1.f}
    };
    std::vector<float> data;
    for (auto const direction : squarePattern)
    {
        const glm::vec2 point = center + semiWidth*direction;
        data.push_back(center.x);
        data.push_back(center.y);
        data.push_back(0.f);
    }glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);


    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*data.size(), data.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}


void Render2D::use()
{
    glBindVertexArray(VAO);
}
