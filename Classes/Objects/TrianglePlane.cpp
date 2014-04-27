//
//  TrianglePlane.cpp
//  distort-2dx
//
//  Created by Simon Andersson on 26/04/14.
//
//

#include "TrianglePlane.h"
#include "GridHelper.h"
#include "MathHelper.h"

USING_NS_CC;


TrianglePlane::TrianglePlane() {
    
}

TrianglePlane::~TrianglePlane() {
    
}

bool TrianglePlane::init() {
    if (!Node::create()) {
        return false;
    }
    return true;
}

void TrianglePlane::setContentSize(const cocos2d::Size &contentSize) {
    Node::setContentSize(contentSize);
    const Size TRIANGLE_SIZE = GRID_SIZE;
    int numberInWidth = contentSize.width/TRIANGLE_SIZE.width;
    int numberInHeight = contentSize.height/TRIANGLE_SIZE.height;
    
    this->removeAllChildren();
    
    for (int y = 0; y < (numberInHeight*2); y++) {
        for (int x = 0; x < (numberInWidth*2); x++) {
            int xx = floor(x / 2.0);
            int yy = floor(y / 2.0);
            
            auto tri = Sprite::create("tri.png");
            if (x % 2 != 0) {
                tri->setRotation(180);
            }
            
            float diff = MathHelper::RandomFloat(0.9, 1.1);
            tri->setColor(MathHelper::randomColor(_color, diff));
            tri->setPosition(Point((xx * TRIANGLE_SIZE.width) + TRIANGLE_SIZE.width/2, (yy * TRIANGLE_SIZE.height) + TRIANGLE_SIZE.height/2));
            this->addChild(tri);
        }
    }
}

void TrianglePlane::setColor(cocos2d::Color3B color) {
    _color = color;
    
    Vector<Node *> children = this->getChildren();
    
    for (size_t i = 0; i < children.size(); i++) {
        auto tri = (Sprite *)children.at(i);
        float diff = MathHelper::RandomFloat(0.9, 1.1);
        tri->setColor(MathHelper::randomColor(color, diff));
    }
}



