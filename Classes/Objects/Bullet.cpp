//
//  Bullet.cpp
//  distort-2dx
//
//  Created by Simon Andersson on 26/04/14.
//
//

#include "Bullet.h"

USING_NS_CC;


Bullet::Bullet() {
    
}

Bullet::~Bullet() {
    
}

bool Bullet::init() {
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255), 4, 2)) {
        return false;
    }
    
    return true;
}

void Bullet::update(float dt) {
    
    Point pos = this->getPosition();
    Point vel = _velocity * dt;
    
    
    Point pt;
    pos.x += roundf(((pos.x + vel.x) - pos.x) * 0.1);
    pos.y -= roundf(((pos.y + vel.y) - pos.y) * 0.1);
    
    pt = pos;
    
    this->setPosition(pt);
}

void Bullet::go() {
    float angle = CC_DEGREES_TO_RADIANS(this->getRotation());
    _velocity = Point(BULLET_MAX_SPEED * cos(angle), BULLET_MAX_SPEED * sin(angle));
}

void Bullet::kill() {
    this->removeFromParent();
}

