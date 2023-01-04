#ifndef GAME_SCENE
#define GAME_SCENE
#define nbLemmings 5

#include "cocos2d.h"
#include "Timer.h"
#include "Pause.h"
#include <CCScheduler.h>
#include <vector>
#include "Accelerate.h"
#include <iostream>

class GameScene : public cocos2d::Scene
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();
    void HUD();
    void rectMenu();
    void lemmings();
    void update(float dt);
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void GameScene::SpawnLemmings(void);
    void Explosion(cocos2d::Ref* pSender);
    void Mining(cocos2d::Ref* pSender);
    void Miningfront(cocos2d::Ref* pSender);
    void Ladder(cocos2d::Ref* pSender);
    void selectionMode();
    void onMouseUp(cocos2d::Event* event);

    cocos2d::Sprite* mySprite;
    cocos2d::Sprite* tile;
    cocos2d::Sprite* mySprite2;
    std::vector<cocos2d::Sprite*> Player;
    cocos2d::TMXTiledMap* map;
    cocos2d::TMXLayer* layerground;
    cocos2d::TMXLayer* layerwall;
    cocos2d::Vec2 origin;
    cocos2d::Rect lemmingsPos;
    cocos2d::Vec2 p;
    cocos2d::Menu* play;
    cocos2d::Size visibleSize;
    cocos2d::Rect* lemmingsRect;
    cocos2d::EventListenerPhysicsContact* contactListener;
    cocos2d::MenuItemImage* hud1;
    cocos2d::MenuItemImage* hud2;
    cocos2d::MenuItemImage* hud3;
    cocos2d::MenuItemImage* hud4;

    bool CanMove = true;
    int i;
    int persoCount = 0;
    float chrono = 0;
    std::vector<std::string> imageLocation;
    std::vector<cocos2d::MenuItemImage*> hud;

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // GAME_SCENE
#pragma once