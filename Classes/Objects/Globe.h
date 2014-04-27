//
//  Globe.h
//  distort-2dx
//
//  Created by Simon Andersson on 27/04/14.
//
//

#ifndef __distort_2dx__Globe__
#define __distort_2dx__Globe__

#include "cocos2d.h"

class Globe : public cocos2d::Sprite
{
public:
    Globe();
    ~Globe();
    CREATE_FUNC(Globe);
    virtual bool init();
    
private:
    virtual void update(float dt);
    
    float _duration = 0.0;
    int _keyframe = 0.0;
    float _keyframeInterval = 0.1;
};

#endif /* defined(__distort_2dx__Globe__) */
