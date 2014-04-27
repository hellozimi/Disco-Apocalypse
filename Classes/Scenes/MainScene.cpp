//
//  MainScene.cpp
//  distort-2dx
//
//  Created by Simon Andersson on 25/04/14.
//
//

#include "MainScene.h"
#include "FightingLayer.h"
#include "GridHelper.h"
#include "MathHelper.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene *MainScene::createScene() {
    auto scene = Scene::create();
    auto layer = MainScene::create();
    
    scene->addChild(layer);
    return scene;
}

bool MainScene::init() {
    Size size = Director::getInstance()->getWinSize();
    if (!LayerColor::initWithColor(Color4B(27, 27, 27, 255), size.width, size.height )) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getWinSize();
    
    // City
    _cityLayer = CityLayer::create();
    _cityLayer->setPositionY(-GRID(0, 35).height);
    this->addChild(_cityLayer);
    //this->setPosition(Point(8.0, 8.0));
    
    _label = Label::createWithTTF("Press any key to start", "BebasNeue.ttf", 32);
    _label->enableShadow();
    
    //_label->enableStroke(Color3B(253, 23, 66), 1.0);
    _cityLayer->addChild(_label);
    
    Point origin = Director::getInstance()->getVisibleOrigin();
    _label->setPosition(Point(origin.x + (visibleSize.width / 2), 40));
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.2);
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("background_loop.wav", true);
    
    
    _introLabel = Label::createWithTTF("The year is 2016 and the human race has fallen. The earth is now controlled by dead pixels. In an underground disco, far beneath the surface of Berlin – a kickass disco dancer is still alive. Not knowing what has happened outside he still rocks his disco moves.\n\nHelp him battle the intruders by using the arrow keys. To make his fingers flick, use the spacebar. ", "BebasNeue.ttf", 22);
    
    this->addChild(_introLabel);
    _introLabel->setMaxLineWidth(GRID(25,0).width);
    _introLabel->setPosition(GRID_POSITION(17.5, 17.5));
    _introLabel->setAlignment(TextHAlignment::CENTER);
    
    auto callback = CallFuncN::create(CC_CALLBACK_1(MainScene::introComplete, this));
    auto sequence = Sequence::create(EaseSineOut::create(MoveTo::create(20.0, Point(0, 0))), callback, NULL);
    _cityLayer->runAction(sequence);
                                     
    
    return true;
}

void MainScene::introComplete(void *sender) {
    _canStartGame = true;
}

                                      
MainScene::MainScene() {
    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->schedule(schedule_selector(MainScene::update));
}

void MainScene::start() {
    Size size = GRID(35, 35);
    _fightingLayer = FightingLayer::create();
    this->addChild(_fightingLayer);
    _fightingLayer->setPosition(0, -size.height);
    
    
    // wer
    {
        auto transition = EaseSineOut::create(MoveTo::create(1.0, Point(0, 0)));
        auto sequence = Sequence::create(transition, NULL);
        _fightingLayer->runAction(sequence);
        
    }
    
    {
        auto transition = EaseSineOut::create(MoveTo::create(1.0, GRID_POSITION(17.5, 52.5)));
        auto sequence = Sequence::create(transition, NULL);
        _introLabel->runAction(sequence);
    }
    {
        auto transition = EaseSineOut::create(MoveTo::create(1.0, Point(0, size.height)));
        auto callbackAction = CallFuncN::create(CC_CALLBACK_1(MainScene::gameShouldStart, this));
        auto sequence = Sequence::create(transition, callbackAction, NULL);
        sequence->setTag(1337);
        
        _cityLayer->runAction(sequence);
    }
}

void MainScene::gameShouldStart(void *sender) {
    log("start game");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0);
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
    if (_canStartGame) {
        _eventDispatcher->removeAllEventListeners();
        this->start();
    }
    else {
        _cityLayer->stopAllActions();
        
        auto callback = CallFuncN::create(CC_CALLBACK_1(MainScene::skipIntroComplete, this));
        auto sequence = Sequence::create(EaseQuadraticActionInOut::create(MoveTo::create(0.5, Point(0, 0))), callback, NULL);
        _cityLayer->runAction(sequence);
    }
}

void MainScene::skipIntroComplete(void *sender) {
    _canStartGame = true;
}

static float __duration = 0.0;

float MainScene::getBeat() {
    return map(pow(cos((__duration*M_PI*2.333333333)), 2.0), 0.0, 1.0, 0.0, 1.0);
}
void MainScene::update(float delta) {
    __duration += delta;
    _label->setTextColor(Color4B(255, 255, 255, map(sinf(__duration*10), -1, 1.0, 127, 255)));
}



