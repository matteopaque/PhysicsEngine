//
// Created by Clef on 1/5/26.
//

#include "ParticleForceRegistry.h"
#include <algorithm>
#include <vector>

void ParticleForceRegistry::addRegistration(int particleID, int generatorID)
{

    registrations.emplace_back(particleID, generatorID);
}


void ParticleForceRegistry::clear()
{
    registrations.clear();
}

void ParticleForceRegistry::removeRegistration(int particleID, int generatorID)
{
    Registration toDelete {particleID, generatorID};
    std::erase(registrations ,toDelete);
}

void ParticleForceRegistry::updateForces(double deltaTime)
{
    std::vector<std::pair<int, int>> toRemove;
    for (const auto & registration : registrations)
    {
        const auto  particle = registration.first;
        if (particles.contains(particle))
        {

        const auto generator = registration.second;
        generators.at(generator)->updateForce(particles.at(particle), deltaTime);
        }else
            toRemove.push_back(registration);
        for (auto remove : toRemove)
        {
            erase(registrations, remove);
        }

    }

}
