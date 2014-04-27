//
//  DiscoLayer.cpp
//  distort-2dx
//
//  Created by Simon Andersson on 27/04/14.
//
//

#include "DiscoLayer.h"
#include "GridHelper.h"
#include "MathHelper.h"
#include "MainScene.h"

#include "Globe.h"

USING_NS_CC;

#define LIGHT_SPEED Point(100, 0)
#define LIGHT_MIN_OPAICTY 50
#define LIGHT_MAX_OPAICTY 100

DiscoLayer::DiscoLayer() {
    this->schedule(schedule_selector(DiscoLayer::update));
}

DiscoLayer::~DiscoLayer() {
    this->unscheduleUpdate();
}

bool DiscoLayer::init() {
    if (!ClippingNode::init()) {
        return false;
    }
    
    auto stencil = LayerColor::create(Color4B(255, 255, 255, 255), GRID(35, 25).width, GRID(35, 25).height);
    
    this->setStencil(stencil);
    
    _lights = new std::vector<Sprite *>();
    
    auto globe = Globe::create();
    globe->setPosition(GRID_POSITION(17.5, 23));
    this->addChild(globe, 999);
    
    return true;
}

cocos2d::Sprite *DiscoLayer::createDiscoLight() {
    return Sprite::create("disco_light.png");
}

void DiscoLayer::spawnLights() {
    if (_state == 0) {
        Sprite *light1 = this->createDiscoLight();
        Sprite *light2 = this->createDiscoLight();
        Sprite *light3 = this->createDiscoLight();
        
        light1->setOpacity(MathHelper::RandomFloat(LIGHT_MIN_OPAICTY, LIGHT_MAX_OPAICTY));
        light2->setOpacity(MathHelper::RandomFloat(LIGHT_MIN_OPAICTY, LIGHT_MAX_OPAICTY));
        light3->setOpacity(MathHelper::RandomFloat(LIGHT_MIN_OPAICTY, LIGHT_MAX_OPAICTY));
        
        light1->setPosition(GRID_POSITION(-1, 6));
        light2->setPosition(GRID_POSITION(-1, 13));
        light3->setPosition(GRID_POSITION(-1, 20));
        this->addChild(light1);
        this->addChild(light2);
        this->addChild(light3);
        
        _lights->push_back(light1);
        _lights->push_back(light2);
        _lights->push_back(light3);
    }
    else {
        Sprite *light1 = this->createDiscoLight();
        Sprite *light2 = this->createDiscoLight();
        
        light1->setOpacity(MathHelper::RandomFloat(LIGHT_MIN_OPAICTY, LIGHT_MAX_OPAICTY));
        light2->setOpacity(MathHelper::RandomFloat(LIGHT_MIN_OPAICTY, LIGHT_MAX_OPAICTY));
        
        light1->setPosition(GRID_POSITION(-1, 10));
        light2->setPosition(GRID_POSITION(-1, 17));
        
        this->addChild(light1);
        this->addChild(light2);
        
        _lights->push_back(light1);
        _lights->push_back(light2);
    }
}

float grapher(float x) {
    return powf(sinf(x * M_PI), 2);
}

float dur = 0.0;
void DiscoLayer::update(float dt) {
    dur += dt;
    
    if (dur > _spawnTimer) {
        dur = 0;
        _state++;
        if (_state > 1) {
            _state = 0;
        }
        
        _spawnTimer = MathHelper::RandomFloat(0.5, 0.65);
        this->spawnLights();
    }
    
    for (size_t i = 0; i < _lights->size(); i++) {
        Sprite *light = _lights->at(i);
        Point vel = LIGHT_SPEED * dt;
        Point pos = light->getPosition();
        pos += vel;
        light->setPosition(pos);
        
        float progress = pos.x /this->getStencil()->getContentSize().width;
        
        light->setScale(map(grapher(progress), 0, 1, 0.9, 0.6));
        
        if (pos.x > this->getStencil()->getContentSize().width + light->getContentSize().width/2) {
            light->removeFromParent();
            _lights->erase(_lights->begin() + i);
            i--;
        }
    }
}


