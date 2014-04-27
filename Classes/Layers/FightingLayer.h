//
//  FightingLayer.h
//  distort-2dx
//
//  Created by Simon Andersson on 26/04/14.
//
//

#ifndef __distort_2dx__FightingLayer__
#define __distort_2dx__FightingLayer__

#include "cocos2d.h"
#include "Player.h"
#include "TrianglePlane.h"
#include "Bullet.h"
#include "Smoke.h"
#include "Enemy.h"
#include "DiscoLayer.h"

class FightingLayer : public cocos2d::Layer
{
public:
    
    FightingLayer();
    ~FightingLayer();
    
    virtual bool init();
    
    CREATE_FUNC(FightingLayer);
    
private:
    
    std::vector<Bullet *> *_bullets;
    std::vector<Smoke *> *_smokes;
    std::vector<Enemy *> *_enemies;
    
    TrianglePlane *_ground;
    
    cocos2d::Label *_scoreLabel;
    
    cocos2d::LayerColor *_fadeBackground = NULL;
    DiscoLayer *_discoLayer;
    
    long _score = 0.0;
    float _playDuration = 0.0;
    
    void shoot();
    
    void updateScore();
    
    void generateSmoke();
    void generateEnemies(void *sender);
    void gameReadyToStart(void *sender);
    void fadeOutCallback(void *sender);
    void update(float dt);
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    
    Player *_player;
    bool _readyToPlayAgain = false;
    
    void start();
    void gameDidEnd();
};

#endif /* defined(__distort_2dx__FightingLayer__) */
