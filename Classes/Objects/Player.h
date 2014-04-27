//
//  Player.h
//  distort-2dx
//
//  Created by Simon Andersson on 26/04/14.
//
//

#ifndef __distort_2dx__Player__
#define __distort_2dx__Player__

#include "cocos2d.h"
#include "Bullet.h"

typedef enum {
    PlayerStateIdle,
    PlayerStateDown,
    PlayerStateWalking
} PlayerState;


class Player : public cocos2d::Sprite
{
public:
    Player();
    ~Player();
    
    virtual bool init();
    
    CREATE_FUNC(Player);
    
    void setVelocity(cocos2d::Point velocity);
    cocos2d::Point getVelocity() const;
    void updatePlayerState(void *sender);
    void updatePlayerForCurrentState();
    
    float getArmRotation() const;
    bool getFlipped() const;
    
    bool isAlive() const;
    void bringToLife();
    
    void kill();
    
    cocos2d::Point getGunPosition() const;
    
private:
    
    void jump();
    void update(float dt);
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    
    void handleKeyboardInput();
    
    mutable cocos2d::Point _velocity;
    
    bool _alive = false;
    bool _canMoveRight;
    bool _canMoveUp;
    bool _canMoveLeft;
    bool _canMoveDown;
    
    bool _flipped;
    
    bool _shiftDown;
    bool _isAirborn;
    
    float _keyframeDuration = 0.1;
    float _animationDuration = 0.0;
    int _currentFrame = 0.0;
    
    cocos2d::Sprite *_arm;
    
    void playerDidDieAnimation(void *sender);
    
    PlayerState _playerState = PlayerStateIdle;
};

#endif /* defined(__distort_2dx__Player__) */
