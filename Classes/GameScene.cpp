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
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    if (!Scene::init())
    {
        return false;
    }

    auto pause = Pause::create();
    addChild(pause,1);
    auto speedup = Accelerate::create();
    addChild(speedup,1);

    HUD();

    auto rectNode = DrawNode::create();
    Vec2 rectangle[4];
    rectangle[0] = Vec2(0, 0);
    rectangle[1] = Vec2(visibleSize.width * 2, 0);
    rectangle[2] = Vec2(0, 20);
    rectangle[3] = Vec2(visibleSize.width * 2, 20);

    Color4F white(1, 1, 1, 1);
    rectNode->drawPolygon(rectangle, 4, white, 1, white);
    this->addChild(rectNode,0);

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
        auto counting = TimerCountDown::create();
        addChild(counting);
        break;
    }
}