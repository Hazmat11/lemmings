#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto listener = EventListenerMouse::create();

    listener->onMouseMove = [](cocos2d::Event* event) {
        // Cast Event to EventMouse for position details like above
        cocos2d::log("Mouse moved event");
    };

    _eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

    HUD();

    return true;
}

void GameScene::HUD() {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    imageLocation = { "mining.png", "explosion.png", "ladder.png", "miningfront.png"};

    for (i = 0; i < 4; i++) {
        auto hud = MenuItemImage::create(imageLocation[i], imageLocation[i], CC_CALLBACK_1(GameScene::test, this));

        if (hud == nullptr ||
            hud->getContentSize().width <= 0 ||
            hud->getContentSize().height <= 0)
        {
            problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
        }
        else
        {
            float x = origin.x + visibleSize.width / 2 + hud->getContentSize().width * i - 40;
            float y = origin.y + hud->getContentSize().height / 2;
            hud->setPosition(Vec2(x, y));
        }

        //origin.y + visibleSize.height - label->getContentSize().height)

        auto play = Menu::create(hud, NULL);
        play->setPosition(Vec2::ZERO);
        this->addChild(play, 1);
    }
}

void GameScene::test(Ref* pSender) {
    switch (i) {
    case 1 :
        Director::getInstance()->end();
    default:
        auto counting = TimerCountDown::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, counting, Color3B(0, 0, 0)));
        break;
    }
}