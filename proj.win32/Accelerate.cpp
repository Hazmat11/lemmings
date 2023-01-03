#include "Accelerate.h"

USING_NS_CC;

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Accelerate::init()
{
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto hud = MenuItemImage::create("speedup.png", "speedup.png", CC_CALLBACK_1(Accelerate::speedUp, this));

    if (hud == nullptr ||
        hud->getContentSize().width <= 0 ||
        hud->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width / 4 * 3;
        float y = origin.y + hud->getContentSize().height / 2;
        hud->setPosition(Vec2(x, y));
    }

    auto play = Menu::create(hud, NULL);
    play->setPosition(Vec2::ZERO);
    this->addChild(play, 1);


    return true;
}

void Accelerate::speedUp(Ref* pSender) {
    /*scheduleUpdate();*/
}

void Accelerate::update(float dt) {
    log("test");
    float speed = 2;
    auto scene = Director::getInstance()->getRunningScene();
    //scene->getPhysicsWorld()->setAutoStep(false);
    scene->getPhysicsWorld()->step(dt * speed);
}