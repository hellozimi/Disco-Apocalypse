//
//  Enemy.h
//  distort-2dx
//
//  Created by Simon Andersson on 27/04/14.
//
//

#ifndef __distort_2dx__Enemy__
#define __distort_2dx__Enemy__

#include "cocos2d.h"
#include "TrianglePlane.h"

class Enemy : public cocos2d::Node
{
public:
    virtual bool init();
    CREATE_FUNC(Enemy);
    
    Enemy();
    ~Enemy();
    void setDirection(int direction);
    int getDirection() const;
    bool getIsAlive() const;
    void jump(void *sender);
    void kill();
private:
    TrianglePlane *_sprite;
    
    void die(void *sender);
    float _duration;
    bool _isAirborn;
    bool _alive;
    int _direction;
    mutable cocos2d::Point _velocity;
    void update(float dt);
};

#endif /* defined(__distort_2dx__Enemy__) */
