//
//  MathHelper.cpp
//  distort-2dx
//
//  Created by Simon Andersson on 26/04/14.
//
//

#include "MathHelper.h"


float MathHelper::RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

cocos2d::Color3B MathHelper::randomColor(cocos2d::Color3B color, float diff) {
    cocos2d::Color3B c = color;
    GLubyte r = c.r * diff;
    GLubyte g = c.g * diff;
    GLubyte b = c.b * diff;
    
    return cocos2d::Color3B(r, g, b);
}