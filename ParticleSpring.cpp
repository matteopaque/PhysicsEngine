//
// Created by Clef on 1/5/26.
//

#include "ParticleSpring.h"


void ParticleSpring::updateForce(Particle& particle, double duration)
{
    auto pos = particle.getPosition();
    const auto anchorToParticle = pos - anchor;
    glm::vec3 force = (float)(springConstant*(glm::length(anchorToParticle) - restlength)) * -glm::normalize(anchorToParticle);
    particle.addForce(force);
}
