//
// Created by Clef on 1/5/26.
//

#include "ParticleForceRegistry.h"
#include <algorithm>
#include <vector>

void ParticleForceRegistry::addRegistration(Particle & particle, ParticleForceGenerator& generator)
{

    registrations.emplace_back(&particle, &generator);
}


void ParticleForceRegistry::clear()
{
    registrations.clear();
}

void ParticleForceRegistry::removeRegistration(Particle& particle, ParticleForceGenerator& generator)
{
    Registration toDelete {&particle, &generator};
    std::erase(registrations ,toDelete);
}

void ParticleForceRegistry::updateForces(double deltaTime)
{
    for (const auto & registration : registrations)
    {
        const auto & particle = registration.first;
        const auto & generator = registration.second;
        generator->updateForce(*particle, deltaTime);
    }
}
