#include "Pause.h"

USING_NS_CC;

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Pause::init()
{
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(Pause::onKeyPressed, this);

    _eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

    return true;
}

void Pause::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_ESCAPE:
        switch (verif) {
        case false:
            pauseMenu();
            Director::getInstance()->pause();
            verif = true;
            break;
        case true:
            this->removeAllChildren();
            Director::getInstance()->resume();
            verif = false;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void Pause::pauseMenu() {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::createWithTTF("Paused", "fonts/Marker Felt.ttf", 60);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height /2));

        // add the label as a child to this layer
        this->addChild(label);
    }
}