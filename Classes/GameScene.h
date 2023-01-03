#ifndef GAME_SCENE
#define GAME_SCENE

#include "cocos2d.h"
#include "Timer.h"
#include "Pause.h"
#include <CCScheduler.h>
#include <vector>
#include "Accelerate.h"

class GameScene : public cocos2d::Scene
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();
    void HUD();
    void rectMenu();
    void lemmings();
    void update(float dt);
    void menuCloseCallback(cocos2d::Ref* pSender);
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void test(cocos2d::Ref* pSender);

    cocos2d::Sprite* mySprite;
    cocos2d::Sprite* tile;
    cocos2d::Sprite* mySprite2;
    cocos2d::TMXTiledMap* map;
    cocos2d::TMXLayer* layer;
    cocos2d::Vec2 origin;
    cocos2d::Size visibleSize;
    cocos2d::Rect* lemmingsRect;
    cocos2d::EventListenerPhysicsContact* contactListener;

    bool CanMove = true;
    int i;

    std::vector<std::string> imageLocation;

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // GAME_SCENE
#pragma once
