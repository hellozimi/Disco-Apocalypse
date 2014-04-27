//
//  Smoke.h
//  distort-2dx
//
//  Created by Simon Andersson on 27/04/14.
//
//

#ifndef __distort_2dx__Smoke__
#define __distort_2dx__Smoke__

#include "cocos2d.h"

class Smoke : public cocos2d::Sprite
{
public:
    
    Smoke();
    
    virtual bool init();
    
    CREATE_FUNC(Smoke);
    void reverse();
private:
    float _offset;
    cocos2d::Point _velocity;
    void update(float dt);
};

#endif /* defined(__distort_2dx__Smoke__) */
