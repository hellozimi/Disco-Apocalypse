//
//  CityLayer.h
//  distort-2dx
//
//  Created by Simon Andersson on 26/04/14.
//
//

#ifndef __distort_2dx__CityLayer__
#define __distort_2dx__CityLayer__

#include "cocos2d.h"
#include "TrianglePlane.h"

class CityLayer : public cocos2d::Layer
{
public:
    CityLayer();
    ~CityLayer();
    
    virtual bool init();
    
    CREATE_FUNC(CityLayer);
    
private:
    TrianglePlane *_skyTrianglePlane;
    cocos2d::Layer *_starLayer;
    
    void generateStars();
};

#endif /* defined(__distort_2dx__CityLayer__) */
