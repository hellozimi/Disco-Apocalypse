//
//  MainScene.h
//  distort-2dx
//
//  Created by Simon Andersson on 25/04/14.
//
//

#ifndef __distort_2dx__MainScene__
#define __distort_2dx__MainScene__

#include "cocos2d.h"
#include "TrianglePlane.h"
#include "CityLayer.h"
#include "FightingLayer.h"

class MainScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene *createScene();
    
    MainScene();
    virtual bool init();
    
    CREATE_FUNC(MainScene);
    
    static float getBeat();
    
private:
    
    TrianglePlane *_skyTrianglePlane;
    CityLayer *_cityLayer;
    FightingLayer *_fightingLayer;
    cocos2d::Label *_label;
    
    void update(float dt);
    void start();
    cocos2d::Label *_introLabel;
    bool _canStartGame = false;
    
    void introComplete(void *sender);
    void skipIntroComplete(void *sender);
    
    void gameShouldStart(void *sender);
    
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
};


#endif /* defined(__distort_2dx__MainScene__) */
