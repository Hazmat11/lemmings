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
    addChild(pause,2);
    auto speedup = Accelerate::create();
    addChild(speedup,2);

    HUD();

    auto rectNode = DrawNode::create();
    Vec2 rectangle[4];
    rectangle[0] = Vec2(0, 0);
    rectangle[1] = Vec2(visibleSize.width * 2, 0);
    rectangle[2] = Vec2(0, 50);
    rectangle[3] = Vec2(visibleSize.width * 2, 50);

    Color4F white(1, 1, 1, 1);
    rectNode->drawPolygon(rectangle, 4, white, 1, white);
    this->addChild(rectNode,1);

    auto counting = TimerCountDown::create();
    addChild(counting, 1);

    initWithPhysics();
    this->getPhysicsWorld()->setDebugDrawMask(true);

    //add contact event listener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);



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
    map = TMXTiledMap::create("map.tmx");
    this->addChild(map, 0, 99);
    layer = map->getLayer("grd 1");
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

void GameScene::HUD() {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    imageLocation = { "mining.png", "explosion.png", "ladder.png", "miningfront.png"};

    for (i = 0; i < 4; i++) {
        auto hud = MenuItemImage::create(imageLocation[i], imageLocation[i], CC_CALLBACK_1(GameScene::HUDSelection, this));

        auto buttonIndex = hud->setTag(i);

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
        this->addChild(play, 2);
    }
}

<<<<<<< HEAD
void GameScene::rectMenu() {
    auto rectNode = DrawNode::create();
    Vec2 rectangle[4];
    rectangle[0] = Vec2(0, 0);
    rectangle[1] = Vec2(visibleSize.width * 2, 0);
    rectangle[2] = Vec2(0, 50);
    rectangle[3] = Vec2(visibleSize.width * 2, 50);

    Color4F white(1, 1, 1, 1);
    rectNode->drawPolygon(rectangle, 4, white, 1, white);
    this->addChild(rectNode, 1);
}

void GameScene::lemmings() {
    initWithPhysics();
    this->getPhysicsWorld()->setDebugDrawMask(true);

    //add contact event listener
    contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

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
}

<<<<<<< HEAD
void GameScene::HUDSelection(Ref* pSender) {
=======

void GameScene::test(Ref* pSender) {
>>>>>>> 7be97cd3e44c17732ac1eff0df6e41edbfe7a0a8
    auto lemmingsRect = mySprite->getBoundingBox();
=======
void GameScene::test(Ref* pSender) {
    auto actualPos = mySprite->getPosition();
>>>>>>> parent of d89da53 (semi working explosion)
    switch (i) {
    case 4 :
        /*for (int i = 0; i < 9; i++) {
            auto tile = layer->getTileAt(actualPos);
            if (tile != nullptr)
            {
<<<<<<< HEAD
                tile = layer->getTileAt(Vec2(i, j));
                if (tile != nullptr)
                {
                    auto tileRect = tile->getBoundingBox();
                    if (tileRect.intersectsRect(lemmingsRect)){
                        layer->removeTileAt(Vec2(i, j));
                    }
                }
=======
                layer->removeTileAt(actualPos);
>>>>>>> parent of d89da53 (semi working explosion)
            }
            else {
                actualPos.y += 50;
            }
        }*/
    default:
        break;
    }
}

void GameScene::update(float dt)
{
    if (CanMove == true)
    {

        auto position = mySprite->getPositionX();

    }
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

}

bool GameScene::onContactBegin(PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    if (nodeA && nodeB)
    {
        if (nodeA->getTag() == 10)
        {
            CanMove = false;
            mySprite->getPhysicsBody()->setVelocity(Vec2(50, -5));
            //nodeB->removeFromParentAndCleanup(false);
        }
        else if (nodeB->getTag() == 10)
        {
            //nodeA->removeFromParentAndCleanup(true);
        }
    }

    //bodies can collide
    return true;
}
