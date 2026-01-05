//
// Created by Clef on 1/5/26.
//

#ifndef OPENGLSETUP_PARTICLEFORCEREGISTRY_H
#define OPENGLSETUP_PARTICLEFORCEREGISTRY_H
#include <memory>

#include "Particle.h"
#include "ParticleForceGenerator.h"


class ParticleForceRegistry
{
    using Registration = std::pair<Particle *, ParticleForceGenerator*>;
    using Registry = std::vector<Registration>;
    Registry registrations;
public:
    void addRegistration(Particle & particle, ParticleForceGenerator& generator);
    void updateForces(double deltaTime);
    void clear();
    void removeRegistration(Particle &particle, ParticleForceGenerator& generator);
};


#endif //OPENGLSETUP_PARTICLEFORCEREGISTRY_H