//
//  Bullet.h
//  distort-2dx
//
//  Created by Simon Andersson on 26/04/14.
//
//

#ifndef __distort_2dx__Bullet__
#define __distort_2dx__Bullet__

#include "cocos2d.h"

#define BULLET_MAX_SPEED 8000.0

class Bullet : public cocos2d::LayerColor
{
public:
    Bullet();
    ~Bullet();
    
    virtual bool init();
    
    CREATE_FUNC(Bullet);
    
    cocos2d::Point getVelocity() const;
    
    bool isAlive();
    
    void go();
    void update(float dt);
    void kill();
    
private:
    
    cocos2d::Point _velocity = cocos2d::Point(0.0, 0.0);
};

#endif /* defined(__distort_2dx__Bullet__) */
