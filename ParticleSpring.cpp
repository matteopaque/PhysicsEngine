//
// Created by Clef on 1/5/26.
//

#include "ParticleSpring.h"


void ParticleSpring::updateForce(Particle& particle, double duration)
{
    auto pos = particle.getPosition();
    const auto anchorToParticle = pos - anchor;
    if (glm::length(anchorToParticle) <= 0.0001)
        return;
    glm::vec3 force = static_cast<float>((springConstant*(glm::length(anchorToParticle) - restlength))) * ((-1.f)*glm::normalize(anchorToParticle));
    particle.addForce(force);
}
