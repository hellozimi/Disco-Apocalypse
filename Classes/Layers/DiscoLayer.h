//
//  DiscoLayer.h
//  distort-2dx
//
//  Created by Simon Andersson on 27/04/14.
//
//

#ifndef __distort_2dx__DiscoLayer__
#define __distort_2dx__DiscoLayer__

#include "cocos2d.h"

class DiscoLayer : public cocos2d::ClippingNode
{
public:
    CREATE_FUNC(DiscoLayer);
    DiscoLayer();
    ~DiscoLayer();
    virtual bool init();
    
private:
    
    void update(float dt) override;
    
    int _state = 0.0;
    float _spawnTimer = 0.6;
    
    std::vector<cocos2d::Sprite *> *_lights;
    
    cocos2d::Sprite *createDiscoLight();
    
    void spawnLights();
};

#endif /* defined(__distort_2dx__DiscoLayer__) */
