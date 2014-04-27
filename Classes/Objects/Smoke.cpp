//
//  Smoke.cpp
//  distort-2dx
//
//  Created by Simon Andersson on 27/04/14.
//
//

#include "Smoke.h"
#include "MathHelper.h"
#include "MainScene.h"

USING_NS_CC;

Smoke::Smoke() {
    this->schedule(schedule_selector(Smoke::update));
}

bool Smoke::init() {
    
    if (!Sprite::initWithFile(round(CCRANDOM_0_1()) == 1 ? "floor_smoke_1.png" : "floor_smoke_2.png")) {
        return false;
    }
    float r = map(CCRANDOM_0_1(), 0, 1, 25, 50);
    if (round(CCRANDOM_0_1()) == 1) {
        r *= -1;
    }
        
    _velocity = Point(r, 0.0);
    
    _offset = MathHelper::RandomFloat(0.5, 1.0);
    this->setOpacity(127);
    return true;
}

void Smoke::reverse() {
    _velocity.x = _velocity.x * -1;
}

float _durr = 0.0;
void Smoke::update(float dt) {
    _durr += dt;
    Point pos = this->getPosition();
    Point vel = _velocity * dt;
    
    Point pt;
    pos.x = pos.x + vel.x;
    
    pt = pos;
    
    this->setPosition(pt);
    this->setRotation(map(roundf(MainScene::getBeat()), 0, 1, -20, 20));
    //this->setRotation(map(sinf((_durr/12.0) + _offset), -1, 1, -3, 3));
}