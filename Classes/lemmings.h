#pragma once
#include "cocos2d.h"
#include <CCScheduler.h>
#include <vector>
class lemmings : public cocos2d::Scene
{
    virtual bool init();

    void update(float dt);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    bool onContactBegin(cocos2d::PhysicsContact& contact);


    // implement the "static create()" method manually
    CREATE_FUNC(lemmings);
    cocos2d::Sprite* mySprite;
    cocos2d::Sprite* mySprite2;
    bool CanMove = true;
};

