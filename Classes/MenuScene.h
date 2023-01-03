#ifndef MENU_SCENE
#define MENU_SCENE

#include "cocos2d.h"
#include "GameScene.h"

class MenuScene : public cocos2d::Scene
{
public:
    GameScene game;
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void playGame(cocos2d::Ref* pSender);
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);

    bool changeScene;
};

#endif // GAME_SCENE
#pragma once