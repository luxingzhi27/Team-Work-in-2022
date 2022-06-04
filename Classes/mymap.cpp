#include "mymap.h"
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
    m_hero->setPosition(Vec2(150,150));

    m_hero->bindMap(m_map);         //绑定地图





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




Scene* MapLayer::createMapScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = MapLayer::create();
    scene->addChild(layer);
    return scene;
}