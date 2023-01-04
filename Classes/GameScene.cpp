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
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    if (!Scene::init())
    {
        return false;
    }

    auto pause = Pause::create();
    addChild(pause,2);
    auto speedup = Accelerate::create();
    addChild(speedup,2);

    HUD();
    rectMenu();

    auto counting = TimerCountDown::create();
    addChild(counting, 1);
    
    lemmings();

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
    layer = map->getLayer("wall");
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

    imageLocation = { "mining.png", "explosion.png", "ladder.png", "miningfront.png" };

    hud = {
    hud1 = MenuItemImage::create(imageLocation[0], imageLocation[0], CC_CALLBACK_1(GameScene::Mining, this)),
    hud2 = MenuItemImage::create(imageLocation[1], imageLocation[1], CC_CALLBACK_1(GameScene::Explosion, this)),
    hud3 = MenuItemImage::create(imageLocation[2], imageLocation[2], CC_CALLBACK_1(GameScene::Miningfront, this)),
    hud4 = MenuItemImage::create(imageLocation[3], imageLocation[3], CC_CALLBACK_1(GameScene::Ladder, this)),
    };
    for (i = 0; i < 4; i++) {
        auto hud = MenuItemImage::create(imageLocation[i], imageLocation[i], CC_CALLBACK_1(GameScene::HUDSelector, this));

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
        float x = origin.x + visibleSize.width / 2 + hud[i]->getContentSize().width * i - 40;
        float y = origin.y + hud[i]->getContentSize().height / 2;
        hud[i]->setPosition(Vec2(x, y));
        play = Menu::create(hud[i], NULL);
        play->setPosition(Vec2::ZERO);
        this->addChild(play, 2);
    }
}

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

    //for (int p = 0; p < 100; p++)
    //{
    //    auto physicsPerso = PhysicsBody::createBox(Size(5.0f, 8.0f),
    //        PhysicsMaterial(0.1f, 1.0f, 0.0f));
    //    perso.push_back(Sprite::create("perso.png", Rect(5, 0, 10, 8)));
    //    perso[p]->addComponent(physicsPerso);
    //    perso[p]->setScale(3.0);
    //    perso[p]->setTag(10);
    //    perso[p]->getPhysicsBody()->setContactTestBitmask(0xFFFFFF0F);
    //    perso[p]->getPhysicsBody()->setDynamic(true);
    //    perso[p]->getPhysicsBody()->setMass(50);
    //    perso[p]->getPhysicsBody()->setRotationEnable(false);
    //    perso[p]->setPosition(Vec2(500, 400));
    //    this->addChild(perso[p], 0);
    //    perso[p]->getPhysicsBody()->setVelocity(Vec2(50+p, -5));
    //}



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


void GameScene::HUDSelector(Ref* pSender) {
void GameScene::Explosion(Ref* pSender) {
    auto lemmingsRect = mySprite->getBoundingBox();
    switch (i) {
    case 4:
        for (int i = 0; i < 32; ++i)
        {
            for (int j = 0; j < 24; ++j)
            {
                tile = layer->getTileAt(Vec2(i, j));
                if (tile != nullptr)
                {
                    auto tileRect = tile->getBoundingBox();
                    if (tileRect.intersectsRect(lemmingsRect)){
                        layer->removeTileAt(Vec2(i, j));
                    }
                }
            }
        }
    default:
        break;
    }
    for (int i = 0; i < 32; ++i)
    {
        for (int j = 0; j < 24; ++j)
        {
            tile = layer->getTileAt(Vec2(i, j));
            if (tile != nullptr)
            {
                auto tileRect = tile->getBoundingBox();
                if (tileRect.intersectsRect(lemmingsRect)) {
                    layer->removeTileAt(Vec2(i, j));
                }
            }
        }
    }
}

void GameScene::Mining(cocos2d::Ref* pSender)
{
}

void GameScene::Miningfront(cocos2d::Ref* pSender)
{
}

void GameScene::Ladder(cocos2d::Ref* pSender)
{
}

void GameScene::SpawnLemmings()
{
    if (persoCount < 100)
    {

        auto physicsPerso2 = PhysicsBody::createBox(Size(5.0f, 8.0f),
            PhysicsMaterial(0.1f, 1.0f, 0.0f));
        perso2.push_back(Sprite::create("perso.png", Rect(5, 0, 10, 8)));
        perso2[persoCount]->addComponent(physicsPerso2);
        perso2[persoCount]->setScale(3.0);
        perso2[persoCount]->setTag(10);
        perso2[persoCount]->getPhysicsBody()->setContactTestBitmask(0xFFFFFF0F);
        perso2[persoCount]->getPhysicsBody()->setDynamic(true);
        perso2[persoCount]->getPhysicsBody()->setMass(50);
        perso2[persoCount]->getPhysicsBody()->setRotationEnable(false);
        perso2[persoCount]->setPosition(Vec2(300, 500));
        this->addChild(perso2[persoCount], 0);
        perso2[persoCount]->getPhysicsBody()->setVelocity(Vec2(50 + persoCount, 0));
        persoCount++;
    }
}
void GameScene::update(float dt)
{
    chrono += dt;
    if (chrono > 0.5)
    {
        SpawnLemmings();
        chrono = 0;
    }
    
    if (CanMove == true)
    {
        auto position = mySprite->getPositionX();
    }
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
        }
        else if (nodeB->getTag() == 10)
        {
        }
    }

    //bodies can collide
    return true;
}
