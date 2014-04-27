//
//  CityLayer.cpp
//  distort-2dx
//
//  Created by Simon Andersson on 26/04/14.
//
//

#include "CityLayer.h"
#include "TrianglePlane.h"
#include "GridHelper.h"
#include "Star.h"
#include "MathHelper.h"

USING_NS_CC;


CityLayer::CityLayer() {
    
}

CityLayer::~CityLayer() {
    
}

void CityLayer::generateStars() {
    int numberOfStars = 10;
    Size minSize = GRID(0, 10);
    Size maxSize = GRID(35, 35);
    for (int i = 0; i < numberOfStars; i++) {
        auto star = Star::create();
        float x = MathHelper::RandomFloat(minSize.width, maxSize.width);
        float y = MathHelper::RandomFloat(minSize.height, maxSize.height);
        star->setPosition(Point(x, y));
        _starLayer->addChild(star);
    }
}

bool CityLayer::init() {
    
    if (!Layer::init()) {
        return false;
    }
    _skyTrianglePlane = TrianglePlane::create();
    _skyTrianglePlane->setPosition(0, 0);
    _skyTrianglePlane->setContentSize(GRID(35, 35*2));
    _skyTrianglePlane->setColor(Color3B(27, 27, 27));
    this->addChild(_skyTrianglePlane);
    
    _starLayer = Layer::create();
    _starLayer->setContentSize(GRID(35, 35));
    this->generateStars();
    this->addChild(_starLayer);
    
    
    auto building1 = TrianglePlane::create();
    building1->setContentSize(GRID(5, 22));
    building1->setColor(Color3B(91, 91, 91));
    building1->setPosition(GRID_POSITION(4, 4));
    this->addChild(building1);
    
    auto building2 = TrianglePlane::create();
    building2->setContentSize(GRID(5, 25));
    building2->setColor(Color3B(55, 55, 55));
    building2->setPosition(GRID_POSITION(16, 4));
    this->addChild(building2);
    
    auto building3 = TrianglePlane::create();
    building3->setContentSize(GRID(5, 21));
    building3->setColor(Color3B(91, 91, 91));
    building3->setPosition(GRID_POSITION(20, 4));
    this->addChild(building3);
    
    auto grass = TrianglePlane::create();
    grass->setContentSize(GRID(35, 1));
    grass->setColor(Color3B(59, 75, 27));
    grass->setPosition(GRID_POSITION(0, 4));
    this->addChild(grass);
    
    auto ground = TrianglePlane::create();
    ground->setContentSize(GRID(35, 4));
    ground->setColor(Color3B(117, 78, 58));
    ground->setPosition(GRID_POSITION(0, 0));
    this->addChild(ground);
    
    return true;
}

