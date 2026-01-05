//
// Created by Clef on 1/5/26.
//

#ifndef OPENGLSETUP_PARTICLESPRING_H
#define OPENGLSETUP_PARTICLESPRING_H
#include "Particle.h"
#include "ParticleForceGenerator.h"
#include <glm/glm.hpp>


class ParticleSpring : public ParticleForceGenerator
{
    glm::vec3 anchor;
    double springConstant;
    double restlength;
public:
    void updateForce(Particle& particle, double duration) override;
    ParticleSpring(glm::vec3 inanchor, double inspringConstant, double inrestlength):
        anchor(inanchor), springConstant(inspringConstant),restlength(inrestlength)
    {}
    inline const glm::vec3 & getAnchor() const
    {
        return anchor;
    }
};


#endif //OPENGLSETUP_PARTICLESPRING_H