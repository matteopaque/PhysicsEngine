//
// Created by Clef on 1/4/26.
//

#ifndef OPENGLSETUP_PARTICLE_H
#define OPENGLSETUP_PARTICLE_H
#include <glm/glm.hpp>
#include <iostream>

class Particle
{
private:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 Acceleration;
    glm::vec3 ForceAccumulate;

    float inverseMass = 1.f;

public:
    float radius = 1.f;
    float dampening = 0.995f;
    void integrate (float deltaTime);
    bool shouldRemove() const;
    void clearForce();
    void addForce(glm::vec3 toAdd);
    Particle(glm::vec3 inposition, glm::vec3 invelocity, float inradius, float mass = 1.f)
        : position(inposition), velocity(invelocity), radius(inradius), Acceleration(glm::vec3({0.f, -10.f, 0.f}))
    {
        inverseMass = 1.f/mass;
        clearForce();
    }
    const glm::vec3  getPosition()
    {
        return position;
    }
};




#endif //OPENGLSETUP_PARTICLE_H
