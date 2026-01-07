//
// Created by Clef on 1/5/26.
//

#ifndef OPENGLSETUP_PARTICLEFORCEREGISTRY_H
#define OPENGLSETUP_PARTICLEFORCEREGISTRY_H
#include <map>
#include <memory>

#include "Particle.h"
#include "ParticleForceGenerator.h"


class ParticleForceRegistry
{
    using Registration = std::pair<int,int>;
    using Registry = std::vector<Registration>;

    Registry registrations;
    std::map<int, Particle>& particles;
    std::map<int, std::unique_ptr<ParticleForceGenerator>>& generators;
public:
    ParticleForceRegistry(std::map<int,Particle>& particles, std::map<int,std::unique_ptr<ParticleForceGenerator>>& generators):
    particles(particles), generators(generators) {}
    void addRegistration(int particleID, int generatorID);
    void updateForces(double deltaTime);
    void clear();
    void removeRegistration(int particleID, int generatorID);
};


#endif //OPENGLSETUP_PARTICLEFORCEREGISTRY_H