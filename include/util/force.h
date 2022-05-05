#ifndef __FORCE_H__
#define __FORCE_H__


#include "util/vec2.h"
#include "util/color.h"
#include "util/rendering.h"
#include <random>
#include <cmath>

#include "particlesystem.h"
#include "util/particleinfo.h"

#include "Tracy.hpp"

class Force : public rendering::ForceInfo {
public:
    
    vec2 strength = {0.1f, 0.1f};
    
  
    virtual vec2 getVelocity(double distance, vec2 difference) = 0;

};


// difference between particle and force is needed
class Gravity : public Force {

public:
    vec2 getVelocity(double distance, vec2 difference) override {
        strength = {0.001f, 0.001f};
        vec2 velocity = {0.0f, 0.0f};

        // Check that distance is not 0    
        if (distance > 0.01) {
            vec2 normalized = difference.normalized();
            //&&difference.x != 0 && difference.y != 0 && difference.x != 0 && difference.y != 0
            //double temp = 0.01 * (1 / distance) * strength.x;
            //velocity = {temp, temp};
            //velocity = strength * 0.03 * (1 / distance);
            velocity.x = float(0.01 * normalized.x * strength.x * (1 / pow(distance,2)));
            velocity.y = float(0.01 * normalized.y * strength.y * (1 / pow(distance,2)));
            
        }

        //if (difference.x != 0) velocity.x = 0.01 * (1 / difference.x) * strength.x;
        //if (difference.y != 0) velocity.y = 0.01 * (1 / difference.y) * strength.y;
       


        return velocity;
    }
    
};

// difference passed but not needed
class Wind : public Force {

public:
    
    double limit = 0.1;

    vec2 getVelocity(double distance, vec2 difference) override {
        strength = {1.0f, 1.0f};

        vec2 velocity = {0.0f, 0.0f};
        
        //double distance = sqrt(pow(difference.x, 2.0) + pow(difference.y, 2.0));

        if (distance < limit) {
            velocity.x = float(0.0001 * strength.x);
            velocity.y = float(0.0001 * strength.y);
        } 
        

        return velocity;
    }
};


#endif  // __FORCE_H__