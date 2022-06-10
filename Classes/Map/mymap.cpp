#include "mymap.h"
#include"SettingandCreating/FastCreating.h"
#include<cstdlib>
#include<ctime>
#include<vector>
#include<algorithm>

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
    BloodBar = BarCreate(Vec2(200, VisibleSize .height-20),"BloodBar.png");
    BloodBar->setScale(1.8,1.2);
    BlueBar = BarCreate(Vec2(200, VisibleSize.height - 40), "BlueBar.png");
    BlueBar->setScale(1.8, 1.2);

    Num = 0;
    auto path = StringUtils::format("ATK:%d", Num);
    label2 = Label::createWithSystemFont("", "fonts/Marker Felt.ttf", 35);
    label2->setTextColor(Color4B::ORANGE);
    label2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    label2->setScaleX(1.35f);
    label2->setPosition(Vec2(90, VisibleSize.height - 90));
    label2->enableShadow();

    m_map = TMXTiledMap::create("desert.tmx");
    m_map->setPosition(Vec2(0, 0));
    this->addChild(m_map);

    int playerHeroType = 3;           //选择英雄种类

    m_hero=chooseHero(playerHeroType,m_hero);
    m_hero->init();
    this->addChild(m_hero);

    label = Label::createWithTTF("Cheese Play!", "fonts/Marker Felt.ttf", 30);
    label->setTextColor(Color4B::ORANGE);
    label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    label->setPosition(Vec2(BlueBar->getPosition())+Vec2(400,0));
    label->setScaleX(1.35f);
    label->enableShadow();
    int aiNum = 9;                         //选择ai数量
    for (int i = 0; i <aiNum ; i++)
    {
        auto aiHeroType = rand() % 4;
        auto ai = Hero::create();
        ai=chooseHero(aiHeroType, ai);
        ais.pushBack(ai);
        ai->setai();
        ai->init();
        addChild(ai);
        ai->bindMap(m_map);
    }


    auto bornGrp = m_map->getObjectGroup("bornpoint");       //获取英雄出生点对象层
    auto bornPoints = bornGrp->getObjects();


    std::vector<int> playerPos;
    srand((unsigned)time(0));
    auto ran = rand() % 10;
    auto playerBorn = bornPoints[ran];
    m_hero->setPosition(playerBorn.asValueMap().at("x").asFloat(), playerBorn.asValueMap().at("y").asFloat());
    playerPos.push_back(ran);

    for (auto i : ais)
    {
        int r = 0;
        while (1)
        {
            //srand((unsigned)time(0));
            r = rand() % 10;
            if (std::count(playerPos.begin(),playerPos.end(),r))
                continue;
            else
            {
                playerPos.push_back(r);
                break;
            }
        }
        auto playerBorn = bornPoints[r];
        i->setPosition(playerBorn.asValueMap().at("x").asFloat(), playerBorn.asValueMap().at("y").asFloat());
        log("%f,%f", playerBorn.asValueMap().at("x").asFloat(), playerBorn.asValueMap().at("y").asFloat());
    }

    


    m_hero->bindMap(m_map);         //绑定地图

    smoke_vec.resize(64);          //初始化毒雾
    for (int cnt = 0; cnt < 64; cnt++)
    {
        smoke_vec[cnt] = Smoke::create("smoke.png");
    }

    //每三十秒产生一圈毒雾
    this->schedule(SEL_SCHEDULE(&MapLayer::createSmoke), 30.0f);



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
    int cnt = 0;
    auto children = getChildren();
    for (auto i : children)
    {
        if (i->getTag() == HERO_TAG)
            cnt++;
    }
    if (m_hero!=nullptr)
    {
        Num = m_hero->getATK();
        auto path = StringUtils::format("ATK:%d", Num);
        label2->setString(path);
        BloodBar->setPercent(double(m_hero->getHP()) / m_hero->getMaxHP() * 100);
        BlueBar->setPercent(double(m_hero->getEnergy() )/ m_hero->getMaxEnergy() * 100);
        if (BlueBar->getPercent() == 100.f)
            label->setVisible(true);
        else
            label->setVisible(false);
        auto winSize = Director::getInstance()->getWinSize();
        int x = MAX(m_hero->getPositionX(), winSize.width / 2);
        int y = MAX(m_hero->getPositionY(), winSize.height / 2);

        x = MIN(x, m_map->getTileSize().width * m_map->getMapSize().width - winSize.width / 2);
        y = MIN(y, m_map->getTileSize().height * m_map->getMapSize().height - winSize.height / 2);

        auto actualPos = Vec2(x, y);
        auto centerView = Vec2(winSize.width / 2, winSize.height / 2);

        auto viewPoint = centerView - actualPos;
        this->setPosition(viewPoint);
    }
    if (m_hero != nullptr && cnt == 1)
    {
        //win
    }
    else if (m_hero == nullptr)
    {
        //defeat
    }
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


        /////////////////////人中毒
        else if (nodeA->getTag() == HERO_TAG && nodeB->getTag() == SMOKE_TAG)
        {
            isConEve = true;
            ConEve = ContactEvents::HeroPoisoning;
            auto hero = dynamic_cast<Hero*>(nodeA);
            auto smoke = dynamic_cast<Smoke*>(nodeB);
            ConEveBe_Hero_Smoke(hero, smoke);
        }
        else if (nodeB->getTag() == HERO_TAG && nodeA->getTag() == SMOKE_TAG)
        {
            isConEve = true;
            ConEve = ContactEvents::HeroPoisoning;
            auto hero = dynamic_cast<Hero*>(nodeB);
            auto smoke = dynamic_cast<Smoke*>(nodeA);
            ConEveBe_Hero_Smoke(hero, smoke);
        }
        ///////////////////////人中大招
        else if (nodeA->getTag() == SPELL_TAG && nodeB->getTag() == HERO_TAG)
        {
            isConEve = true;
            ConEve = ContactEvents::HeroHurt;
            auto spell = dynamic_cast<Bullet*>(nodeA);
            auto hero = dynamic_cast<Hero*>(nodeB);
            ConEve_Hero_Bullet(hero, spell);
        }
        else if (nodeB->getTag() == SPELL_TAG && nodeA->getTag() == HERO_TAG)
        {
            isConEve = true;
            ConEve = ContactEvents::HeroHurt;
            auto spell = dynamic_cast<Bullet*>(nodeB);
            auto hero = dynamic_cast<Hero*>(nodeA);
            ConEve_Hero_Bullet(hero, spell);
        }
        /////////////////////////////宝箱中大招
        else if (nodeA->getTag() == SPELL_TAG && nodeB->getTag() == TREASURE_TAG)
        {
            isConEve = true;
            ConEve = ContactEvents::TreasureHurt;
            auto spell = dynamic_cast<Bullet*>(nodeA);
            auto treasure = dynamic_cast<Treasure*>(nodeB);
            ConEve_Treasure_Bullet(treasure,spell);
        }
        else if (nodeB->getTag() == SPELL_TAG && nodeA->getTag() == TREASURE_TAG)
        {
            isConEve = true;
            ConEve = ContactEvents::TreasureHurt;
            auto spell = dynamic_cast<Bullet*>(nodeB);
            auto treasure = dynamic_cast<Treasure*>(nodeA);
            ConEve_Treasure_Bullet(treasure, spell);
        }
    }

  return true;
  
}

void MapLayer::onContactSeparate(cocos2d::PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    if (nodeA && nodeB)
    {
        if (nodeA->getTag() == HERO_TAG && nodeB->getTag() == SMOKE_TAG)
        {
            auto hero = dynamic_cast<Hero*>(nodeA);
            auto smoke = dynamic_cast<Smoke*>(nodeB);
            ConEveEnd_Hero_Smoke(hero, smoke);
        }
        else if (nodeB->getTag() == HERO_TAG && nodeA->getTag() == SMOKE_TAG)
        {
            isConEve = true;
            ConEve = ContactEvents::HeroPoisoning;
            auto hero = dynamic_cast<Hero*>(nodeB);
            auto smoke = dynamic_cast<Smoke*>(nodeA);
            ConEveEnd_Hero_Smoke(hero, smoke);
        }
    }

}


void MapLayer::ConEve_Hero_Bullet(Hero* hero,Bullet* bullet)
{
    if (hero->isAI())
        log("enermy get hurt");
    else
        log("hero get hurt");
    bullet->fillenergy();
    hero->getHurt(bullet->getATK());
    bullet->onHit();
  
}
void MapLayer::ConEve_Treasure_Bullet(Treasure* treasure, Bullet* bullet)
{
    log("treasure get hurt");
    log("map size x:%d,y:%d", m_map->getMapSize().width, m_map->getMapSize().height);
    treasure->getHurt(bullet->getATK());
    bullet->onHit();

}

void MapLayer::ConEve_Hero_Diamond(Hero* hero, Diamond* dia)
{
    if (hero->isAI())
        log("enermy get diamond");
    else
        log("hero get diamond");
    hero->getDiamond();
    dia->removeFromParentAndCleanup(true);
}

void MapLayer::ConEveBe_Hero_Smoke(Hero* hero, Smoke* smoke)
{
    if (hero->isAI())
        log("enermy get into smoke");
    else
        log("hero get into smoke");
    hero->setPoisoning(true);
}

void MapLayer::ConEveEnd_Hero_Smoke(Hero* hero, Smoke* smoke)
{
    if (hero->isAI())
        log("enermy get outof smoke");
    else
        log("hero get outof smoke");
    hero->setPoisoning(false);
   
}

void MapLayer::createSmoke(float dlt)
{
    if (smoke_index < 64)
    {
        for (int cnt = 0; cnt < smoke_range; cnt++, smoke_index++)//下
        {
            int x = ((8 - smoke_range) / 2 + cnt) * 192;
            int y = (8 - smoke_range) / 2 * 192;

            smoke_vec[smoke_index]->setPosition(x, y);
            smoke_vec[smoke_index]->RunfadeIn();
            this->addChild(smoke_vec[smoke_index]);
        }
        for (int cnt = 0; cnt < smoke_range; cnt++, smoke_index++)//上
        {
            int x = ((8 - smoke_range) / 2 + cnt) * 192;
            int y = (8-((8-smoke_range)/2)-1) * 192;
            smoke_vec[smoke_index]->setPosition(x, y);
            smoke_vec[smoke_index]->RunfadeIn();
            this->addChild(smoke_vec[smoke_index]);
        }
        for (int cnt = 1; cnt < smoke_range-1; cnt++, smoke_index++)//左
        {
            int x = (8 - smoke_range) / 2 * 192;
            int y = ((8 - smoke_range) / 2 + cnt) * 192;
            smoke_vec[smoke_index]->setPosition(x, y);
            smoke_vec[smoke_index]->RunfadeIn();
            this->addChild(smoke_vec[smoke_index]);
        }
        for (int cnt = (8 - smoke_range) / 2+1; cnt < (8-(8-smoke_range)/2)-1; cnt++, smoke_index++)//右
        {
            int x = (8-(8-smoke_range)/2-1) * 192;
            int y = cnt * 192;
            smoke_vec[smoke_index]->setPosition(x, y);
            smoke_vec[smoke_index]->RunfadeIn();
            this->addChild(smoke_vec[smoke_index]);
        }
        smoke_range -= 2;
    }
    
}

void MapLayer::ConEve_Hero_Spell(Hero* hero, Bullet* spell)
{
    if(hero->isAI())
        log("enermy get spell hurt");
    else
        log("hero get spell hurt");
    hero->getHurt(spell->getATK());
    spell->onHit();
}

Hero* MapLayer::chooseHero(int choose,Hero* _hero)
{
    switch (choose)
    {
        case 0:
            _hero = Shirley::create();
            break;
        case 1:
            _hero = Nita::create();
            break;
        case 2:
            _hero = Colt::create();
            break;
        case 3:
            _hero = Leon::create();
            break;
        defalt:
            break;
    }
    return _hero;
}



Scene* MapLayer::createMapScene()
{
    //auto VisibleSize = Director::getInstance()->getVisibleSize();
    //auto tw = LayerColor::create(Color4B::GRAY);
    //tw->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    //tw->setContentSize(Size(450, 80));
    //tw->setPosition(0, VisibleSize.height-80);

    auto scene = Scene::createWithPhysics();
    auto layer = MapLayer::create();

    scene->addChild(layer);
    //scene->addChild(tw);
    scene->addChild(layer->label);
    scene->addChild(layer->label2);
    scene->addChild(layer->BloodBar);
    scene->addChild(layer->BlueBar);
    auto ExitImage = Close_create([](Ref* ref, Widget::TouchEventType type)
        {
            switch (type) {
            case Widget::TouchEventType::ENDED:
                Director::getInstance()->end();
                break;
            default:
                break;
            }
        });
    scene->addChild(ExitImage);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto menuImage = MenuImageCreate();
    menuImage->setCallback(CC_CALLBACK_1(MapLayer::ButtonEvent, layer, scene));
    auto pMenu = MenuCreate("Menu", menuImage,
        Vec2(visibleSize.width - 90, visibleSize.height - 45));
    scene->addChild(pMenu);
    return scene;
}


void MapLayer::ButtonEvent(cocos2d::Ref* pSender, Scene* scene)
{
    //Director::getInstance()->stopAnimation();
    auto layer = MenuLayer::create();
    scene->addChild(layer);
}