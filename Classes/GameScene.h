#ifndef GAME_SCENE
#define GAME_SCENE

#include "cocos2d.h"
//#include "Timer.h"

class GameScene : public cocos2d::Scene
{
public:
    //TimerCountDown timer;

    static cocos2d::Scene* createScene();

    virtual bool init();
    void HUD();

    int i;

    // a selector callback
    void test(cocos2d::Ref* pSender);

    std::vector<std::string> imageLocation;

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // GAME_SCENE
#pragma once
