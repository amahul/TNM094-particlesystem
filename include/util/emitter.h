#ifndef __EMITTER_H__
#define __EMITTER_H__

#include "util/vec2.h"
#include "util/color.h"
#include "util/rendering.h"
#include <random>
#include <cmath>
#include <iostream>

#include "particlesystem.h"
#include "util/particleinfo.h"

#include "Tracy.hpp"


class Emitter : public rendering::EmitterInfo{
    public:
    
    vec2 velocity = {0.0f, 0.0f};
    //virtual vec2 getVelocity() = 0;
    virtual void addParticle(std::vector<vec2> &velocities,
                             std::vector<rendering::ParticleInfo> &particles,
                             rendering::ParticleInfo particle, double dt) = 0;

};



class Directional : public Emitter {

 public:

     void addParticle(std::vector<vec2> &velocities, std::vector<rendering::ParticleInfo> &particles,
         rendering::ParticleInfo particle, double dt) override {
         // If the remainder of (time / 0.05) is less than 0.0005
         // This is to make sure that less than one particle is created every frame
         // Numbers decided by testing
         if (fmod(dt, 0.05) < 0.0005) {

             // Partiklarna sprutas ut åt höger
             velocity.y = float(cos((rand() / (float)(RAND_MAX)*2.5) + 0.1) / 10);
             velocity.x = 0.5f;

             particle.color = {rand() / (float)(RAND_MAX), rand() / (float)(RAND_MAX),
                               rand() / (float)(RAND_MAX)};  // Color between (0-1) per channel
             particle.radius = {2.0f +
                                rand() / (float)(RAND_MAX)*6.0f};  // Radius between (1.0-10.0)

             particles.push_back(particle);
             velocities.push_back(velocity);
             //std::cout << particles.size() << " ";
         }

     }
};

class Uniform : public Emitter {

public:
    void addParticle(std::vector<vec2> &velocities, std::vector<rendering::ParticleInfo> &particles,
                     rendering::ParticleInfo particle, double dt) override {
        if (fmod(dt, 0.05) < 0.0005) {
            // Partiklarna sprutas ut åt alla håll
            velocity.y = (rand() / (float)(RAND_MAX)) * 2.0f - 1.0f;
            velocity.x = (rand() / (float)(RAND_MAX)) * 2.0f - 1.0f;

            particle.color = {rand() / (float)(RAND_MAX), rand() / (float)(RAND_MAX),
                              rand() / (float)(RAND_MAX)};  // Color between (0-1) per channel
            particle.radius = {2.0f +
                               rand() / (float)(RAND_MAX)*6.0f};  // Radius between (1.0-10.0)

            particles.push_back(particle);
            velocities.push_back(velocity);
        }
    }
};


class Explosion : public Emitter {

public:
    

    // Amount of particles for every explosion
    int n_particles = 50;
 
    void addParticle(std::vector<vec2>& velocities, std::vector<rendering::ParticleInfo>& particles,
                     rendering::ParticleInfo particle, double dt) override {
        // Partiklar sprutas ut var tredje sekund
        if (fmod(dt, 3) < 0.0005) {
            for (int i = 0; i < n_particles; i++) {
                
                //Partiklarna sprutas ut åt alla håll
                velocity.y = (rand() / (float)(RAND_MAX)) * 2.0f - 1.0f;
                velocity.x = (rand() / (float)(RAND_MAX)) * 2.0f - 1.0f;

                particle.color = {rand() / (float)(RAND_MAX), rand() / (float)(RAND_MAX),
                                  rand() / (float)(RAND_MAX)};  // Color between (0-1) per channel
                particle.radius = {2.0f +
                                   rand() / (float)(RAND_MAX)*6.0f};  // Radius between (1.0-10.0)

                particles.push_back(particle);
                velocities.push_back(velocity);
            }

        }
    }
 
};


#endif  // __EMITTERINFO_H__
