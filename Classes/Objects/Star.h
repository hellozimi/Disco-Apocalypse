//
//  Star.h
//  distort-2dx
//
//  Created by Simon Andersson on 26/04/14.
//
//

#ifndef __distort_2dx__Star__
#define __distort_2dx__Star__

#include "cocos2d.h"

class Star : public cocos2d::LayerColor
{
public:
    Star();
    ~Star();
    
    virtual bool init();
    
    CREATE_FUNC(Star);

private:
    
    virtual void update(float dt);
};

#endif /* defined(__distort_2dx__Star__) */
