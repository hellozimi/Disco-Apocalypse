//
//  Globe.cpp
//  distort-2dx
//
//  Created by Simon Andersson on 27/04/14.
//
//

#include "Globe.h"
#include "GridHelper.h"

USING_NS_CC;

#define GLOBE_1     "globe_1.png"
#define GLOBE_2     "globe_2.png"
#define GLOBE_3     "globe_2.png"
#define GLOBE_4     "globe_3.png"
#define GLOBE_5     "globe_4.png"
#define GLOBE_6     "globe_5.png"
#define GLOBE_7     "globe_6.png"
#define GLOBE_8     "globe_7.png"
#define GLOBE_9     "globe_9.png"
#define GLOBE_10    "globe_10.png"
#define GLOBE_11    "globe_11.png"
#define GLOBE_12    "globe_12.png"

Globe::Globe() {
    this->schedule(schedule_selector(Globe::update));
}

Globe::~Globe() {
    this->unschedule(schedule_selector(Globe::update));
}

bool Globe::init() {
    if (!Sprite::initWithFile(GLOBE_1)) {
        return false;
    }
    
    this->setAnchorPoint(Point(0.5, 1));
    
    auto line = LayerColor::create(Color4B(47, 47, 47, 255), 2, GRID(0, 2).height);
    line->setAnchorPoint(Point(0.5, 0));
    line->setPosition(GRID_POSITION(2, 4));
    this->addChild(line);
    
    return true;
}

void Globe::update(float dt) {
    _duration += dt;
    
    if (_duration > _keyframeInterval) {
        _duration = 0;
        _keyframe++;
        
        if (_keyframe > 16) {
            _keyframe = 1;
        }
        
        int keyname = _keyframe > 12 ? 12 : _keyframe;
        
        char buf[50];
        sprintf(buf, "globe_%i.png", keyname);
        
        this->setTexture(buf);
    }
    
}

