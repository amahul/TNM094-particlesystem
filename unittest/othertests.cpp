#include "catch2.h"
#include "particlesystem.h"
#include "util\emitter.h"
#include "util/vec2.h"
#include <cmath>

// Random float (2,3)
float rnd() { return 2.0f + rand() / (float)(RAND_MAX+1); };

TEST_CASE("ParticleSize", "[particleSystem]") {
    {
        // Default constructor
        rendering::createWindow();
         ParticleSystem p;

         Emitter* E1 = new Uniform;

         double dt = 0.05;
         int n_particles = 1;

        
         //Här blir det fel :(
         p.createParticles(E1, dt);


        // std::cout << p.particles.size();
       
        //rendering::destroyWindow();
        REQUIRE(p.particles.size() == n_particles);
    }
}
TEST_CASE("RandomNumber", "[randomNumber]") {
    {

        int amount = 15;
        float num;

        for (size_t i = 0; i < amount; i++) {
           num = rnd();
           REQUIRE(num <= 3);
           REQUIRE(num >= 2);
        }
    
    }
}

TEST_CASE("DistanceDifference", "[distanceDifference]") {
    {

        //rendering::createWindow();
        ParticleSystem p;

        Emitter* E1 = new Uniform;
        Force* F1 = new Gravity;

        
        double dt = 0.05;
        
        p.createParticles(E1, dt);

        vec2 forcePos = F1->position;
        vec2 partPos = p.particles[0].position;

        rendering::destroyWindow();


       vec2 difference = {forcePos.x - partPos.x, forcePos.y - partPos.y};
       double distance = sqrt(pow(difference.x, 2.0) + pow(difference.y, 2.0));

       

       REQUIRE(distance >= 0);
       REQUIRE(distance >= difference.x);
       REQUIRE(distance >= difference.y);

    }
}

TEST_CASE("Explosion", "[explosion]") {
    {
        ParticleSystem p;
        Explosion E3;

        //Kolla så det finns 50 partiklar i explotion
        REQUIRE(E3.n_particles == 50);
    }
    {
        ParticleSystem p;
        Explosion E3;

        std::vector<rendering::ParticleInfo> particles;
        rendering::ParticleInfo particle;
        std::vector<vec2> velocities;
        double dt = 3.0;

        E3.addParticle(velocities, particles, particle, dt);


        // Kolla så det finns 50 partiklar från explotion i particles
        REQUIRE(particles.size() == 50);
    }
}