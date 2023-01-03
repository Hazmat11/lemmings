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

    void update(float dt);

    void menuCloseCallback(cocos2d::Ref* pSender);
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    cocos2d::Sprite* mySprite;
    cocos2d::Sprite* mySprite2;
    cocos2d::TMXTiledMap* map;
    cocos2d::TMXLayer* layer;

    bool CanMove = true;

    int i;

    // a selector callback
    void test(cocos2d::Ref* pSender);

    std::vector<std::string> imageLocation;

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // GAME_SCENE
#pragma once
