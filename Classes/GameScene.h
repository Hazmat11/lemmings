#ifndef GAME_SCENE
#define GAME_SCENE

#include "cocos2d.h"
#include <iostream>

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void onMouseMove(cocos2d::Event* event);
    void update(float dt);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // GAME_SCENE
#pragma once
