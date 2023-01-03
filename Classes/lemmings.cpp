#include "lemmings.h"

USING_NS_CC;

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool lemmings::init()
{
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    initWithPhysics();
    this->getPhysicsWorld()->setDebugDrawMask(true);

    //add contact event listener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(MainScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("forest.png");

    if (sprite == nullptr)
    {
        problemLoading("'forest.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    auto physicsBody = PhysicsBody::createBox(Size(5.0f, 8.0f),
        PhysicsMaterial(0.1f, 1.0f, 0.0f));
    auto physicsBody2 = PhysicsBody::createBox(Size(5.0f, 8.0f),
        PhysicsMaterial(0.1f, 1.0f, 0.0f));
    mySprite = Sprite::create("perso.png", Rect(5, 0, 10, 8));
    mySprite->addComponent(physicsBody);
    mySprite->setScale(3.0);
    mySprite->setTag(10);
    mySprite->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
    mySprite->getPhysicsBody()->setDynamic(true);
    mySprite->getPhysicsBody()->setMass(50);
    mySprite->getPhysicsBody()->setRotationEnable(false);
    mySprite2 = Sprite::create("perso.png", Rect(5, 0, 10, 8));
    mySprite2->addComponent(physicsBody2);
    mySprite2->setScale(3.0);
    //mySprite2->setTag(5);
    mySprite2->getPhysicsBody()->setContactTestBitmask(0xFFFFFFF);
    mySprite2->getPhysicsBody()->setDynamic(true);


    if (mySprite == nullptr)
    {
        problemLoading("'perso.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        mySprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        mySprite2->setPosition(Vec2(600, 400));
        // add the sprite as a child to this layer
        this->addChild(mySprite, 0);
        this->addChild(mySprite2, 0);

    }
    scheduleUpdate();
    auto map = TMXTiledMap::create("map.tmx");
    this->addChild(map, 0, 99);
    auto layer = map->getLayer("grd 1");
    for (int i = 0; i < 32; ++i)
    {
        for (int j = 0; j < 24; ++j)
        {
            auto tile = layer->getTileAt(Vec2(i, j));
            if (tile != nullptr)
            {
                PhysicsBody* physicmap = PhysicsBody::createBox(Size(32, 32),
                    PhysicsMaterial(0.1f, 1.0f, 0.0f));
                physicmap->setDynamic(false);
                tile->addComponent(physicmap);
                tile->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
            }

        }
    }
    return true;
}