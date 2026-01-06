//
// Created by Clef on 1/6/26.
//

#ifndef OPENGLSETUP_LINE_H
#define OPENGLSETUP_LINE_H
#include <glm/glm.hpp>

class Line
{
public:
    glm::vec3 p1;
    glm::vec3 p2;
    Line(glm::vec3 P1, glm::vec3 P2) : p1(P1), p2(P2){}
    glm::vec3 p1ToP2() const
    {
        return p2 - p1;
    }
    glm::vec3 IntersectWithSphere(glm::vec3 center, float radius)
    {
        auto D = glm::normalize(p1ToP2());
        auto M = p1-center;
        const auto B = 2*(glm::dot(D,M));
        const auto C = glm::dot(M,M)-std::powf(radius,2);
        const float discriminant = std::pow(B,2.f)-4*C;
        if (discriminant < 0)
            return glm::vec3(0.f);
        if (discriminant==0)
        {
            const float T = -(B/2);
            if (T >= 0)
                return center - (p1 = T*D);
            return glm::vec3(0.f);
        }
        const float T1 = (-B+std::sqrtf(discriminant))/2.f;
        const float T2 = (-B-std::sqrtf(discriminant))/2.f;
        const float T = std::min(T1, T2);
        if (T>=0)
        {
            return center-(p1 + D*T);
        }
        return glm::vec3(0.f);

    }
};


#endif //OPENGLSETUP_LINE_H