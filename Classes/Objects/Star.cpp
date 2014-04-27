//
//  Star.cpp
//  distort-2dx
//
//  Created by Simon Andersson on 26/04/14.
//
//

#include "Star.h"
#include "MathHelper.h"

USING_NS_CC;

#define STAR_COLOR Color4B(254, 238, 78, 255)

Star::Star() {
    this->schedule(schedule_selector(Star::update));
}

Star::~Star() {
    
}

bool Star::init() {
    if (!LayerColor::initWithColor(STAR_COLOR, 4, 4)) {
        return false;
    }
    this->setContentSize(Size(4, 4));
    
    return true;
}

void Star::update(float dt) {
    float diff = MathHelper::RandomFloat(0.85, 1.00);
    this->setColor(MathHelper::randomColor(Color3B(STAR_COLOR.r, STAR_COLOR.g, STAR_COLOR.b), diff));
}