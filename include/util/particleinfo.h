#ifndef __PARTICLEINFO_H__
#define __PARTICLEINFO_H__

#include "util/vec2.h"
#include "util/color.h"

struct ParticleInfo {
    // add feat: radius change by user
    constexpr ParticleInfo() = default;
    constexpr ParticleInfo(vec2 position, float radius, Color color, float lifetime)
        : position(position), radius(radius), color(color), lifetime(lifetime) {}

    vec2 position{};  // Call default contructor for vec2
    vec2 velocity{}; 
    vec2 force{}; 

    float radius = 15.f;
    Color color{1.0,0.8,0.2};
    float lifetime = 60.f;
};

#endif  // __PARTICLEINFO_H__