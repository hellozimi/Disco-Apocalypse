//
//  FightingLayer.cpp
//  distort-2dx
//
//  Created by Simon Andersson on 26/04/14.
//
//

#include "FightingLayer.h"
#include "TrianglePlane.h"
#include "GridHelper.h"
#include "MainScene.h"
#include "MathHelper.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

FightingLayer::FightingLayer() {
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(FightingLayer::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(FightingLayer::onKeyReleased, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->schedule(schedule_selector(FightingLayer::update));
}

FightingLayer::~FightingLayer() {
    
}

bool FightingLayer::init() {
    
    if (!Layer::init()) {
        return false;
    }
    
    _bullets = new std::vector<Bullet *>();
    _smokes = new std::vector<Smoke *>();
    _enemies = new std::vector<Enemy *>();
    
    auto background = TrianglePlane::create();
    
    background->setContentSize(GRID(35, 35));
    background->setColor(Color3B(117, 78, 58));
    this->addChild(background);
    
    _ground = TrianglePlane::create();
    
    _ground->setContentSize(GRID(35, 25));
    _ground->setColor(Color3B(84, 56, 42));
    _ground->setPosition(GRID_POSITION(0, 2));
    this->addChild(_ground);
    
    
    _player = Player::create();
    _ground->addChild(_player);
    
    this->generateSmoke();
    
    _scoreLabel = Label::createWithTTF("0", "BebasNeue.ttf", 32);
    _scoreLabel->setAlignment(TextHAlignment::CENTER);
    _scoreLabel->setPosition(Point(_ground->getContentSize().width / 2, _ground->getContentSize().height + 100 ));
    this->addChild(_scoreLabel);
    
    _discoLayer = DiscoLayer::create();
    _ground->addChild(_discoLayer);
    
    this->start();
    
    return true;
}

void FightingLayer::start() {
    _readyToPlayAgain = false;
    _score = 0;
    _playDuration = 0.0;
    
    _player->setPosition(Point( this->getContentSize().width/2, 0));
    _player->bringToLife();
    this->updateScore();
    this->generateEnemies(NULL);
}

void FightingLayer::generateSmoke() {
    float w = this->getContentSize().width;
    for (int i = 0; i < 50; i++) {
        auto smoke = Smoke::create();
        smoke->setPosition(Point(CCRANDOM_0_1() * w, 16));
        _ground->addChild(smoke, 999);
        _smokes->push_back(smoke);
    }
}

void FightingLayer::generateEnemies(void *sender) {
    
    if (!_player->isAlive()) {
        return;
    }
    
    auto enemy = Enemy::create();
    
    int direction = roundf(CCRANDOM_0_1()) == 0 ? -1 : 1;
    enemy->setDirection(direction);
    
    if (direction == -1) {
        enemy->setPosition(Point(_ground->getContentSize().width + enemy->getContentSize().width, 0));
    }
    else {
        enemy->setPosition(Point(-enemy->getContentSize().width, 0));
    }
    
    _ground->addChild(enemy);
    
    enemy->jump(NULL);
    _enemies->push_back(enemy);
    
    auto delay = DelayTime::create(MAX(0.3, 5.0 - ((_playDuration / 2.5) / 3)));
    auto callback = CallFuncN::create(CC_CALLBACK_1(FightingLayer::generateEnemies, this));
    auto sequence = Sequence::create(delay, callback, NULL);
    
    this->runAction(sequence);
}

void FightingLayer::update(float dt) {
    
    _playDuration += dt;
    
    Rect rect = Rect(0, 0, _ground->getContentSize().width, _ground->getContentSize().height);
    // Update bullets
    for (std::vector<Bullet *>::size_type i = 0; i != _bullets->size(); i++) {
        Bullet *bullet = _bullets->at(i);
        bullet->update(dt);
        
        if (!rect.containsPoint(bullet->getPosition())) {
            bullet->kill();
            _bullets->erase(_bullets->begin() + i);
            i--;
            continue;
        }
        
        for (std::vector<Enemy *>::size_type j = 0; j != _enemies->size(); j++) {
            Enemy *enemy = _enemies->at(j);
            
            // Check if bullet hits
            if (enemy->getBoundingBox().containsPoint(bullet->getPosition())) {
                _score += 10;
                // Remove enemy
                //enemy->removeFromParent();
                enemy->kill();
                _enemies->erase(_enemies->begin() + j);
                j--;
                
                // REmove bullet
                bullet->kill();
                _bullets->erase(_bullets->begin() + i);
                i--;
                
                updateScore();
                
                break;
            }
        }
    }
    
    
    for (std::vector<Smoke *>::size_type i = 0; i != _smokes->size(); i++) {
        Smoke *smoke = _smokes->at(i);
        Point position = smoke->getPosition();
        if (position.x < 0) {
            position.x = 0;
            smoke->reverse();
        }
        else if (position.x > rect.size.width) {
            position.x = rect.size.width;
            smoke->reverse();
        }
    }
    
    
    for (std::vector<Enemy *>::size_type i = 0; i != _enemies->size(); i++) {
        Enemy *enemy = _enemies->at(i);
        
        // Check if outside
        bool isOutside = (enemy->getDirection() == -1 && enemy->getPosition().x < 0) || (enemy->getDirection() == 1 && enemy->getPosition().x > _ground->getContentSize().width);
        if (isOutside) {
            enemy->removeFromParent();
            _enemies->erase(_enemies->begin() + i);
            i--;
            continue;
        }
        
        // Check if hits player
        
        if (_player->getBoundingBox().intersectsRect(enemy->getBoundingBox()) && _player->isAlive()) {
            _player->kill();
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("die_sound.wav");
            this->gameDidEnd();
            break;
        }
    }
    if (_player->isAlive()) {
        Point playerPosition = _player->getPosition();
        if (playerPosition.x < _player->getContentSize().width) {
            playerPosition.x = _player->getContentSize().width;
            _player->setPosition(playerPosition);
        }
        else if (playerPosition.x > _ground->getContentSize().width -_player->getContentSize().width) {
            _player->setPositionX(_ground->getContentSize().width -_player->getContentSize().width);
        }
    }
}

void FightingLayer::gameDidEnd() {
    _readyToPlayAgain = false;
    this->stopAllActions();
    for (std::vector<Enemy *>::size_type i = 0; i != _enemies->size(); i++) {
        Enemy *enemy = _enemies->at(i);
        enemy->kill();
        _enemies->erase(_enemies->begin() + i);
        i--;
    }
    
    if (_fadeBackground == NULL) {
        _fadeBackground = LayerColor::create(Color4B(0, 0, 0, 0), GRID(35, 35).width, GRID(35, 35).height);
    }
    _fadeBackground->removeAllChildren();
    
    auto callback = CallFuncN::create(CC_CALLBACK_1(FightingLayer::gameReadyToStart, this));
    auto sequence = Sequence::create(EaseQuadraticActionInOut::create(FadeTo::create(0.4, 100)), callback, NULL);
    _fadeBackground->runAction(sequence);
    
    char buff[100];
    sprintf(buff, "%li points", _score);
    
    auto scoreLabel = Label::createWithTTF(buff, "BebasNeue.ttf", 50);
    scoreLabel->setPosition(Point(_fadeBackground->getContentSize().width / 2, _fadeBackground->getContentSize().height - 150));
    _fadeBackground->addChild(scoreLabel);
    
    auto nextLabel = Label::createWithTTF("Press any key to play again", "BebasNeue.ttf", 32);
    nextLabel->setPosition(Point(_fadeBackground->getContentSize().width / 2, _fadeBackground->getContentSize().height - 200));
    _fadeBackground->addChild(nextLabel);
    
    this->addChild(_fadeBackground);
}

void FightingLayer::gameReadyToStart(void *sender) {
    _readyToPlayAgain = true;
}

void FightingLayer::updateScore() {
    
    char buff[100];
    sprintf(buff, "%li", _score);
    
    Sequence *sequence = Sequence::createWithTwoActions(
                                                        EaseQuadraticActionOut::create(ScaleTo::create(0.05, 1.5)),
                                                        EaseQuadraticActionOut::create(ScaleTo::create(0.05, 1.0))
                                                        );
    
    _scoreLabel->runAction(sequence);
    _scoreLabel->setString(buff);
}

void FightingLayer::shoot() {
    auto bullet = Bullet::create();
    bullet->setRotation(_player->getArmRotation());
    _ground->addChild(bullet);
    
    Point position = _player->getPosition();
    bullet->setPosition(_player->getGunPosition());
    _bullets->push_back(bullet);
    
    bullet->go();
    
    int idx = (round(CCRANDOM_0_1()) * 2.0)+1;
    char buffer[50];
    sprintf(buffer, "shoot_%i.wav", idx);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(buffer);
}

void FightingLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
        // Shoot
        this->shoot();
    }
}

void FightingLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
    if (!_player->isAlive() && _readyToPlayAgain) {
        this->start();
        auto callback = CallFuncN::create(CC_CALLBACK_1(FightingLayer::fadeOutCallback, this));
        auto sequence = Sequence::create(EaseQuadraticActionOut::create(FadeTo::create(0.4, 0.0)), callback, NULL);
        _fadeBackground->runAction(sequence);
    }
}

void FightingLayer::fadeOutCallback(void *sender) {
    _fadeBackground->removeFromParent();
    _fadeBackground = NULL;
}

