#include "particlesystem.h"
#include "util/particleinfo.h"

#include "Tracy.hpp"
#include <cmath>
#include <random>

namespace {
constexpr float Pi = 3.141592654f;
const float Tau = 2.f * Pi;
}  // namespace

// Create new particles from Emitter
void ParticleSystem::createParticles(Emitter* E, double dt) {

    rendering::ParticleInfo particle;
    vec2 velocity = {0.5f, 0.0f};

    particle.lifetime = 10.0f;
    particle.position = {E->position.x, E->position.y};  // Position between (-1,1) = Screen extent

    E->addParticle(velocities, particles, particle, dt);
}

void ParticleSystem::update(std::vector<Force*> forces, double dt) {

    for (size_t i = 0; i < particles.size(); i++) {
        particles[i].lifetime -= float(dt);  // Remove delta time from lifetime

        if (particles[i].lifetime < 0) {
            // Detroy old particles
            particles.erase(particles.begin() + i);  // Remove from vector at index i
            velocities.erase(velocities.begin() + i);
        }
    }
    
    // Loop through each particle
    for (size_t i = 0; i < particles.size(); i++) {

       
        vec2 partPos = particles[i].position;

        for (int j = 0; j < forces.size(); j++) {
            vec2 forcePos = forces[j]->position;

            // Difference and distance between particle and force
            vec2 difference = {forcePos.x - partPos.x, forcePos.y - partPos.y};
            // Euclidian distance
             double distance = sqrt(pow(difference.x, 2.0) + pow(difference.y, 2.0));

            // If particle inside force range
            
            //  velocities[i].x += float(forces[j]->setStrengthX() * difference.x * dt);
            //  velocities[i].y += float(forces[j]->setStrengthY() * difference.y * dt);
            velocities[i] += forces[j]->getVelocity(distance, difference);
            
            //if (distance < 0.01) {  // Set lifetime to 0 if hit black hole
            //   particles[i].lifetime = 0;
                
            
        }

        // Update position
        particles[i].position.x += float(velocities[i].x * dt);
        particles[i].position.y += float(velocities[i].y * dt);

    }

    // @TODO: Update the state of the particle system, move particles forwards, spawn new
    // particles, destroy old particles, and apply effects
}

void ParticleSystem::render(std::vector<Emitter*> emitters, std::vector<Force*> forces) {
    // @TODO: Render the particles, emitters and what not contained within the system
 
    // Particles
    rendering::renderParticles(particles);

    // Emitters
    std::vector<rendering::EmitterInfo> allEmitters;
    for (size_t i = 0; i < emitters.size(); i++) {
        rendering::EmitterInfo e;
        vec2 v = {emitters[i]->position.x, emitters[i]->position.y};
        e.position = v;
        allEmitters.push_back(e);
    }
    rendering::renderEmitters(allEmitters);

    //Forces
    std::vector<rendering::ForceInfo> allForces;
    for (size_t i = 0; i < forces.size(); i++) {
        rendering::ForceInfo f;
        vec2 v = {forces[i]->position.x, forces[i]->position.y};
        f.position = v;
        allForces.push_back(f);
    }
    rendering::renderForces(allForces);
}