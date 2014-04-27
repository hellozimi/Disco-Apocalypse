//
//  Enemy.cpp
//  distort-2dx
//
//  Created by Simon Andersson on 27/04/14.
//
//

#include "Enemy.h"
#include "MathHelper.h"
#include "GridHelper.h"
#include "MainScene.h"

#define MAX_VELOCITY Point(6000.0, -7600)
#define MIN_VELOCITY Point(5000.0, -6500)

USING_NS_CC;

Enemy::Enemy() {
    this->schedule(schedule_selector(Enemy::update));
}

Enemy::~Enemy() {
    this->unschedule(schedule_selector(Enemy::update));
}

bool Enemy::init() {
    if (!Node::init()) {
        return false;
    }
    
    _sprite = TrianglePlane::create();
    _sprite->setPosition(0, 0);
    _sprite->setContentSize(GRID(1, 1));
    _sprite->setColor(Color3B(255, 0, 255));
    this->addChild(_sprite);
    
    this->setContentSize(GRID(1, 1));
    
    this->setAnchorPoint(Point(0, 0));
    _alive = true;
    
    return true;
}

void Enemy::setDirection(int dir) {
    _direction = dir;
    
    this->setAnchorPoint(Point(0.5, 0));
}

int Enemy::getDirection() const {
    return _direction;
}

bool Enemy::getIsAlive() const {
    return _alive;
}

void Enemy::jump(void *sender) {
    if (!_alive) {
        return;
    }
    
    _velocity.x = MathHelper::RandomFloat(MIN_VELOCITY.x, MAX_VELOCITY.x) * _direction;
    _velocity.y = MathHelper::RandomFloat(MIN_VELOCITY.y, MAX_VELOCITY.y);
    
    _isAirborn = true;
    
    // Repeat
    auto updateStateDelay = DelayTime::create(MathHelper::RandomFloat(1.0, 2.0));
    auto callbackAction = CallFuncN::create(CC_CALLBACK_1(Enemy::jump, this));
    auto sequence = Sequence::create(updateStateDelay, callbackAction, NULL);
    this->runAction(sequence);
}

void Enemy::kill() {
    _alive = false;
    
    _velocity.x = 0.0;
    
    auto easing = EaseSineOut::create(ScaleBy::create(2.0, 1.5, 0.0));
    auto callback = CallFuncN::create(CC_CALLBACK_1(Enemy::die, this));
    auto sequence = Sequence::create(easing, callback, NULL);
    this->runAction(sequence);
}
void Enemy::die(void *sender) {
    this->removeAllChildren();
    this->removeFromParent();
}

void Enemy::update(float dt) {
    _duration += dt;
    Point pos = this->getPosition();
    Point vel = _velocity * dt;
    
    Point pt;
    pos.x += roundf(((pos.x + vel.x) - pos.x) * 0.1);
    pos.y -= roundf(((pos.y + vel.y) - pos.y) * 0.1);
    
    // Jumping
    if (_isAirborn) {
        _velocity.y += 550; // Some kind of gravity
    }
    
    // Fix pos
    if (pos.y < 0.0 && _isAirborn) {
        pos.y = 0.0;
        if (_isAirborn) {
            _isAirborn = false;
            _velocity.y = 0;
        }
    }
    
    pt = pos;
    
    this->setPosition(pt);
    
    float angle = CC_RADIANS_TO_DEGREES(_velocity.getAngle());
    if (_velocity.y > 0.0 || !_isAirborn) {
        angle = 0;
    }
    else if (_velocity.y < 0.0 && _isAirborn && _direction == -1) {
        angle -= 180;
    }
    
    this->setRotation(angle);
    if (_alive) {
        
        if (_isAirborn) {
            this->setScaleX(map(fabsf(vel.x), 0, 50, 1.0, 1.4));
            this->setScaleY(map(fabsf(vel.y), 0, 50, 1.0, 0.7));
        }
        else {
            this->setScaleX(map(MainScene::getBeat(), 0.0, 1.0, 1.0, 1.5));
            this->setScaleY(map(MainScene::getBeat(), 0.0, 1.0, 1.0, 0.5));
        }
    }
    
    
    _velocity.x = _velocity.x * 0.8;
}