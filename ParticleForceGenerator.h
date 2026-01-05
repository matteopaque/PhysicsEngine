//
// Created by Clef on 1/5/26.
//

#ifndef OPENGLSETUP_PARTICLEFORCEGENERATOR_H
#define OPENGLSETUP_PARTICLEFORCEGENERATOR_H
#include "Particle.h"

class ParticleForceGenerator
{
public:
    virtual ~ParticleForceGenerator() = default;
    virtual void updateForce(Particle &particle, double duration) = 0;
};

#endif //OPENGLSETUP_PARTICLEFORCEGENERATOR_H