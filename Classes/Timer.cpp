#include "Timer.h"

USING_NS_CC;

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool TimerCountDown::init()
{
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    timertxt = Label::createWithTTF("cool", "fonts/Marker Felt.ttf", 40.0f);
    timertxt->setTextColor(Color4B::RED);

    float x = origin.x + timertxt->getContentSize().width * 2;
    float y = origin.y + timertxt->getContentSize().height / 2;

    timertxt->setPosition(Vec2(x, y));
    addChild(timertxt, 1);
    timeCounter = 90.0f;
    this->scheduleUpdate();

    return true;
}

void TimerCountDown::update(float delta) {
    if (timeCounter > 1.f) {
        timeCounter -= delta;
        auto val2 = trunc(timeCounter);
        std::string val;
        val += std::to_string(ceilf(val2));
        timertxt->setString(val);
    }
    if (timeCounter <= 0) {
        timeCounter = 0;
        //GAME OVER
    }
}