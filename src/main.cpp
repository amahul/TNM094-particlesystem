#include "Tracy.hpp"
#include "particlesystem.h"
#include "util/rendering.h"
#include "util\emitter.h"

#include <cmath>
#include <cstdlib>

// Simple random functions to get started
// Random float (0,1)
float rnd() {
    return rand() / (float)(RAND_MAX);
}

// Random float (-1,1)
float srnd() {
    return rnd() * 2.0f - 1.0f;
}

int main(int, char**) {
    rendering::createWindow();

    ParticleSystem particleSystem;

    std::vector<Emitter*> emitters; // All emitters
    std::vector<Force*> forces;  // All forces

    // Create emitters
    Directional* E1 = new Directional;
    Uniform* E2 = new Uniform;
    Explosion* E3 = new Explosion; 

    // Update emitters position
    E1->position = {0, 0};
    E2->position = {-0.5, -0.5};
    E3->position = {-0.5, 0.5};

    // Save emitters in vector
    emitters.push_back(E1);
    emitters.push_back(E2);
    emitters.push_back(E3);


    // Create forces
    Gravity* F1 = new Gravity;
    Wind* F2 = new Wind;

    // Update forces position
    F1->position = {-0.5, 0.0};
    F2->position = {0.5, 0.0};
    F2->limit = 0.5;
    forces.push_back(F1);
    forces.push_back(F2);


    double t = 0.0;
    float speed = 0.5f;
    bool isRunning = true;
    while (isRunning) {
        const float dt = rendering::beginFrame();
        t += dt;

        // Implement particlesystem for every emitter
        for (int i = 0; i < emitters.size(); i++) {
            particleSystem.createParticles(emitters[i], t);
        }

        // Update and render particlesystems
        particleSystem.update(forces, dt * speed);
        particleSystem.render(emitters, forces);

        {
            ui::GuiScope ui;  // Initiates and finalizes UI rendering upon
                              // construction/destruction
            // @TODO: Replace this example code with your own UI elements
            //ui::text("I'm text!");
            ui::sliderFloat("Simulation speed", speed, 0.001f, 3.0f);

            if (ui::button("New directional emitter")) {          
                // Create new emitter
                Directional* Enew = new Directional;      
                Enew->position = {srnd(), srnd()};

                emitters.push_back(Enew);
            }
            if (ui::button("New uniform emitter")) {
                // Create new emitter
                Uniform* Enew = new Uniform;
                Enew->position = {srnd(), srnd()};

                emitters.push_back(Enew);
            }
            if (ui::button("New explotion emitter")) {
                // Create new emitter
                Explosion* Enew = new Explosion;
                Enew->position = {srnd(), srnd()};

                emitters.push_back(Enew);
            }

            if (ui::button("New gravity")) {
                // Create new gravity
                Gravity* F = new Gravity;
                F->position = {srnd(), srnd()};

                forces.push_back(F);
            }

            if (ui::button("New wind")) {
                // Create new wind
                Wind* F = new Wind;
                F->position = {srnd(), srnd()};
                F->limit = 0.5;

                forces.push_back(F);
            }

             if (ui::button("Remove emitter")) {
                // Remove first emitter
                 if (emitters.size() > 0)
                 emitters.erase(emitters.begin());
               
            }

             if (ui::button("Remove force")) {
                 // Remove first force
                 if (forces.size() > 0)
                 forces.erase(forces.begin());
             }


            if (ui::button("Close application")) {
                isRunning = false;
            }
        }

        isRunning &= rendering::endFrame();
    }

    rendering::destroyWindow();

    return EXIT_SUCCESS;
}