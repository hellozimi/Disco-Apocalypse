//
//  TrianglePlane.h
//  distort-2dx
//
//  Created by Simon Andersson on 26/04/14.
//
//

#ifndef __distort_2dx__TrianglePlane__
#define __distort_2dx__TrianglePlane__

#include "cocos2d.h"

class TrianglePlane : public cocos2d::Node
{
public:
    TrianglePlane();
    ~TrianglePlane();
    
    CREATE_FUNC(TrianglePlane);
    
    void setColor(cocos2d::Color3B color);
    
    virtual bool init();
    void setContentSize(const cocos2d::Size &contentSize) override;
    
private:
    mutable cocos2d::Color3B _color = cocos2d::Color3B(255, 255, 255);
};

#endif /* defined(__distort_2dx__TrianglePlane__) */
