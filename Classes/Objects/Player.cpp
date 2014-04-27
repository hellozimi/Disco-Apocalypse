//
//  Player.cpp
//  distort-2dx
//
//  Created by Simon Andersson on 26/04/14.
//
//

#include "Player.h"
#include "MathHelper.h"
#include "MainScene.h"

USING_NS_CC;

#pragma mark - Player

#define PLAYER_IDLE_TEXTURE "character_idle.png"
#define PLAYER_ARM_TEXTURE "character_arm.png"
#define PLAYER_DOWN_TEXTURE "character_down.png"
#define PLAYER_WALK_LEFT_TEXTURE "character_move_left_up.png"
#define PLAYER_WALK_RIGHT_TEXTURE "character_move_right_up.png"

#define PLAYER_MAXSPEED 2800

Player::Player() {
    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->schedule(schedule_selector(Player::update));
}

Player::~Player() {
}

void Player::updatePlayerState(void *sender) {
    /*
     bool isMoving = _canMoveLeft || _canMoveRight;
     
     float delay = isMoving ? 0.1 : 0.5;
     
     auto updateStateDelay = DelayTime::create(delay);
     auto callbackAction = CallFuncN::create(CC_CALLBACK_1(Player::updatePlayerState, this));
     auto sequence = Sequence::create(updateStateDelay, callbackAction, NULL);
     this->runAction(sequence);
     
     if (_playerState == PlayerStateDown) {
     _playerState = PlayerStateIdle;
     }
     else {
     _playerState = PlayerStateDown;
     }
     
     this->updatePlayerForCurrentState();
     */
}

void Player::updatePlayerForCurrentState() {
    if (!_alive) {
        return;
    }
    
    if (_playerState == PlayerStateIdle) {
        this->setTexture(PLAYER_IDLE_TEXTURE);
        
        switch (_currentFrame) {
            case 0: {
                this->setTexture(PLAYER_IDLE_TEXTURE);
                _arm->setPosition(6, 37);
            } break;
            case 1: {
                this->setTexture(PLAYER_DOWN_TEXTURE);
                _arm->setPosition(6, 31);
            } break;
            default:
                this->setTexture(PLAYER_IDLE_TEXTURE);
                break;
        }
    }
    else if (_playerState == PlayerStateDown) {
        this->setTexture(PLAYER_DOWN_TEXTURE);
        _arm->setPosition(6, 31);
    }
    else if (_playerState == PlayerStateWalking) {
        switch (_currentFrame) {
            case 0:
                this->setTexture(PLAYER_WALK_LEFT_TEXTURE);
                break;
            case 1:
                this->setTexture(PLAYER_IDLE_TEXTURE);
                break;
            case 2:
                this->setTexture(PLAYER_WALK_RIGHT_TEXTURE);
                break;
            default:
                this->setTexture(PLAYER_IDLE_TEXTURE);
                break;
        }
    }
}

bool Player::init() {
    if (!Sprite::initWithFile(PLAYER_IDLE_TEXTURE)) {
        return false;
    }
    
    this->setContentSize(Size(10, 10));
    
    this->setAnchorPoint(Point(0.5, 0));
    
    _arm = Sprite::create("character_idle_arm.png");
    _arm->setAnchorPoint(Point(0.15, 0.899));
    
    this->addChild(_arm);
    
    //this->updatePlayerState(NULL);
    this->updatePlayerForCurrentState();
    //_arm->setRotation(-45.0);
    return true;
}

void Player::setVelocity(cocos2d::Point velocity) {
    _velocity = velocity;
}

Point Player::getVelocity() const {
    return _velocity;
}

bool Player::isAlive() const {
    return _alive;
}

bool Player::getFlipped() const {
    return _flipped;
}

void Player::kill() {
    auto callback = CallFuncN::create(CC_CALLBACK_1(Player::playerDidDieAnimation, this));
    auto sequence = Sequence::create(
                                     EaseQuadraticActionOut::create(
                                                                    ScaleTo::create(0.2, 0.0, 0.0)
                                                                    ), callback, NULL);
    this->runAction(sequence);
    _alive = false;
}

void Player::playerDidDieAnimation(void *sender) {
    //this->removeFromParent();
}

void Player::bringToLife() {
    _alive = true;
    _flipped = false;
    auto sequence = Sequence::create(
                                     EaseQuadraticActionOut::create(
                                                                    ScaleTo::create(0.4, 1.0, 1.0)
                                                                    ), NULL);
    this->runAction(sequence);
}

float Player::getArmRotation() const {
    if (_flipped) {
        return (_arm->getRotation() * -1) + 180;
    }
    return _arm->getRotation();
}

Point Player::getGunPosition() const {
    Point pt = this->getPosition() + _arm->getPosition();
    
    Point gunPosition = Point(18 -this->getAnchorPoint().x * this->getContentSize().width, -2);
    pt.x -= this->getAnchorPoint().x * this->getContentSize().width;
    pt.y -= this->getAnchorPoint().y * this->getContentSize().height;
    float angle = CC_DEGREES_TO_RADIANS(this->getArmRotation());
    pt = pt + Point(gunPosition.x * cos(angle), (gunPosition.x) * sin(-angle));
    return pt;
}

static float _dur = 0;

void Player::update(float dt) {
    _dur += dt;
    
    if (_alive) {
        this->handleKeyboardInput();
    }
    
    Point pos = this->getPosition();
    Point vel = _velocity * dt;
    
    
    Point pt;
    pos.x += roundf(((pos.x + vel.x) - pos.x) * 0.1);
    pos.y -= roundf(((pos.y + vel.y) - pos.y) * 0.1);
    
    // Jumping
    if (_isAirborn) {
        _velocity.y += 550; // Some kind of gravity
    }
    
    // Fix pos
    if (pos.y < 0.0 && _isAirborn) {
        pos.y = 0.0;
        if (_isAirborn) {
            _isAirborn = false;
            _velocity.y = 0;
            
            _playerState = PlayerStateIdle;
            this->updatePlayerForCurrentState();
        }
    }
    
    pt = pos;
    
    this->setPosition(pt);
    
    //_arm->setRotation(map(pow(cos((_dur*M_PI*2.333333333)), 2.0), 0.0, 1.0, -20.0, 20.0));
    _arm->setRotation(map(MainScene::getBeat(), 0, 1, -20, 20));
    _velocity.x = _velocity.x * 0.8;
    
    
    bool isMoving = (_canMoveLeft || _canMoveRight) && !_isAirborn;
    if (isMoving) {
        if (_playerState != PlayerStateWalking) {
            _animationDuration = 0.0;
            _playerState = PlayerStateWalking;
        }
        
        _animationDuration += dt;
        
        if (_animationDuration > _keyframeDuration) {
            _animationDuration = 0.0;
            _currentFrame++;
            
            if (_currentFrame > 2) {
                _currentFrame = 0;
            }
            
            this->updatePlayerForCurrentState();
        }
    }
    else if(_playerState == PlayerStateIdle) {
        
        _animationDuration += dt;
        
        if (_animationDuration > 0.428571429) {
            _animationDuration = 0.0;
            _currentFrame++;
            
            if (_currentFrame > 1) {
                _currentFrame = 0;
            }
            
            this->updatePlayerForCurrentState();
        }
    }
    else if (!_isAirborn && _playerState != PlayerStateIdle) {
        _playerState = PlayerStateIdle;
        this->updatePlayerForCurrentState();
    }
}

void Player::handleKeyboardInput() {
    Point vel = _velocity;
    if (_canMoveLeft) {
        this->setScaleX(-1);
        _flipped = true;
        vel.x = -PLAYER_MAXSPEED;
    }
    else if(_canMoveRight) {
        this->setScaleX(1);
        _flipped = false;
        vel.x = PLAYER_MAXSPEED;
        
    }
    
    _velocity = vel;
}

void Player::jump() {
    if (_isAirborn) { return; }
    
    _isAirborn = true;
    _velocity.y = -8000;
}

void Player::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
    switch (keyCode) {
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            _canMoveLeft = true;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
            //_canMoveUp = true;
            if (_alive) {
                _playerState = PlayerStateDown;
                this->updatePlayerForCurrentState();
                this->jump();
            }
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            _canMoveRight = true;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            _canMoveDown = true;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_SHIFT:
            _shiftDown = true;
            break;
        default:
            break;
    }
}

void Player::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
    switch (keyCode) {
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            _canMoveLeft = false;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
            _canMoveUp = false;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            _canMoveRight = false;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            _canMoveDown = false;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_SHIFT:
            _shiftDown = false;
            break;
            
        default:
            break;
    }
}

