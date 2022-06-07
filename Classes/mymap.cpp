#include "mymap.h"
#include<cstdlib>
#include<ctime>

USING_NS_CC;

bool MapLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    //添加调度器
    this->scheduleUpdate();

    auto VisibleSize = Director::getInstance()->getVisibleSize();

    m_map = TMXTiledMap::create("desert.tmx");
    m_map->setPosition(Vec2(0, 0));
    this->addChild(m_map);

    m_hero = Shirley::create();
    m_hero->init();
    this->addChild(m_hero);
    
    auto bornGrp = m_map->getObjectGroup("bornpoint");       //获取英雄出生点对象层
    auto bornPoints = bornGrp->getObjects();
    srand((unsigned)time(0));
    auto playerBorn = bornPoints[rand() % 10];
    m_hero->setPosition(playerBorn.asValueMap().at("x").asFloat(), playerBorn.asValueMap().at("y").asFloat());

    m_hero->bindMap(m_map);         //绑定地图


    //放置宝箱
    auto treasureGrp = m_map->getObjectGroup("treasure");
    auto treasurePoints = treasureGrp->getObjects();
    for (auto i : treasurePoints)
    {
        auto treasure = Treasure::create("treasure.png");
        this->addChild(treasure);
        treasure->setPosition(i.asValueMap().at("x").asFloat(), i.asValueMap().at("y").asFloat());
    }

    auto dia = Diamond::create("diamond.png");
    dia->setPosition(Vec2(400, 400));
    dia->run_action();
    this->addChild(dia);

    //注册碰撞监听器
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(MapLayer::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

 

    return true;
}



cocos2d::TMXTiledMap* MapLayer::getMap() const
{
    return m_map;
}

void MapLayer::update(float dlt)
{
    Node::update(dlt);

    auto winSize = Director::getInstance()->getWinSize();
    int x = MAX(m_hero->getPositionX(), winSize.width / 2);
    int y = MAX(m_hero->getPositionY(), winSize.height / 2);

    x = MIN(x, m_map->getTileSize().width * m_map->getMapSize().width - winSize.width / 2);
    y = MIN(y, m_map->getTileSize().height * m_map->getMapSize().height - winSize.height / 2);

    auto actualPos = Vec2(x, y);
    auto centerView = Vec2(winSize.width / 2, winSize.height / 2);

    auto viewPoint = centerView-actualPos;
    this->setPosition(viewPoint);


}

bool MapLayer::onContactBegin(cocos2d::PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    if (nodeA && nodeB)
    {
        ///////////////////人物中弹
        if (nodeA->getTag() == BULLET_TAG&& nodeB->getTag()==HERO_TAG)
        {
            isConEve=true;
            ConEve = ContactEvents::HeroHurt;
            auto bullet = dynamic_cast<Bullet*>(nodeA);
            auto hero = dynamic_cast<Hero*>(nodeB);
            ConEve_Hero_Bullet(hero,bullet);
        }
        else if (nodeB->getTag() == BULLET_TAG && nodeA->getTag() == HERO_TAG)
        {
            isConEve = true;
            ConEve = ContactEvents::HeroHurt;
            auto bullet = dynamic_cast<Bullet*>(nodeB);
            auto hero = dynamic_cast<Hero*>(nodeA);
            ConEve_Hero_Bullet(hero, bullet);
        }


        /////////////////////////////宝箱中弹
        else if (nodeA->getTag() == BULLET_TAG&&nodeB->getTag()==TREASURE_TAG)
        {
            isConEve = true;
            ConEve = ContactEvents::TreasureHurt;
            auto bullet = dynamic_cast<Bullet*>(nodeA);
            auto treasure = dynamic_cast<Treasure*>(nodeB);
            ConEve_Treasure_Bullet(treasure, bullet);
        }
        else if (nodeB->getTag() == BULLET_TAG && nodeA->getTag() == TREASURE_TAG)
        {
            isConEve = true;
            ConEve = ContactEvents::TreasureHurt;
            auto bullet = dynamic_cast<Bullet*>(nodeB);
            auto treasure = dynamic_cast<Treasure*>(nodeA);
            ConEve_Treasure_Bullet(treasure, bullet);
        }

        ///////////////////////////////人获取宝石
        else if(nodeA->getTag() == DIAMOND_TAG && nodeB->getTag() == HERO_TAG)
        { 
            isConEve = true;
            ConEve = ContactEvents::getDiamond;
            auto dia = dynamic_cast<Diamond*>(nodeA);
            auto hero = dynamic_cast<Hero*>(nodeB);
            ConEve_Hero_Diamond(hero,dia);
        }
        else if (nodeB->getTag() == DIAMOND_TAG && nodeA->getTag() == HERO_TAG)
        {
            isConEve = true;
            ConEve = ContactEvents::getDiamond;
            auto dia = dynamic_cast<Diamond*>(nodeB);
            auto hero = dynamic_cast<Hero*>(nodeA);
            ConEve_Hero_Diamond(hero, dia);
        }
    }

    return true;
  
}

void MapLayer::ConEve_Hero_Bullet(Hero* hero,Bullet* bullet)
{
    log("hero get hurt");
    hero->getHurt(bullet->getATK());
    bullet->onHit();
    bullet->fillenergy();
    
}
void MapLayer::ConEve_Treasure_Bullet(Treasure* treasure, Bullet* bullet)
{
    log("treasure get hurt");
    treasure->getHurt(bullet->getATK());
    bullet->onHit();

}

void MapLayer::ConEve_Hero_Diamond(Hero* hero, Diamond* dia)
{
    log("hero get diamond");
    hero->getDiamond();
    dia->removeFromParentAndCleanup(true);
}



Scene* MapLayer::createMapScene()
{
    auto scene = Scene::createWithPhysics();
   // scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = MapLayer::create();
    scene->addChild(layer);
    return scene;
}