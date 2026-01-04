//
// Created by Clef on 1/4/26.
//

#include "Particle.h"
#include <iostream>


void Particle::integrate(float deltaTime)
{
    position = position + (velocity * deltaTime);
    velocity *= std::powf(dampening, deltaTime);
    auto accelSum = Acceleration + inverseMass*ForceAccumulate;
    velocity = velocity + (accelSum * deltaTime);

    clearForce();
}

bool Particle::shouldRemove() const
{
    if (position.y < -20.f)
        return true;
    return false;
}

void Particle::clearForce()
{
    ForceAccumulate = glm::vec3(0.f);
}

void Particle::addForce(glm::vec3 toAdd)
{
    ForceAccumulate += toAdd;
}
