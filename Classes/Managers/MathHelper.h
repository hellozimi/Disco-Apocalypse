//
//  MathHelper.h
//  distort-2dx
//
//  Created by Simon Andersson on 26/04/14.
//
//

#ifndef distort_2dx_MathHelper_h
#define distort_2dx_MathHelper_h

#include "cocos2d.h"

class MathHelper
{
public:
    static float RandomFloat(float a, float b);
    static cocos2d::Color3B randomColor(cocos2d::Color3B color, float diff);
};


// Map
static inline float map(float x, float in_min, float in_max, float out_min, float out_max) {
    return ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

// Clamp
static inline float clamp(float value, float min, float max) {
    return MIN(max, MAX(min, value));
}

// Lerp
static inline float lerpf(float a, float b, float t) {
    return (a + (b - a) * t);
}

#endif
