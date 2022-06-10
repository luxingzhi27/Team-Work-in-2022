#pragma once
#ifndef __MAP_LAYER_H__
#define __MAP_LAYER_H__


#include"actor/shirley.h"
#include"actor/nita.h"
#include"actor/colt.h"
#include"actor/leon.h"
#include"const/const.h"
#include"actor/hero.h"
#include"Article/Article.h"
#include"Article/Bullet.h"
#include"Article/Smoke.h"
#include "MenuLayer/MenuLayer.h"
class MapLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createMapScene();
    virtual bool init();
    cocos2d::TMXTiledMap* getMap() const;
    void update(float dlt);
    CREATE_FUNC(MapLayer);
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void onContactSeparate(cocos2d::PhysicsContact& contact);
    void ConEve_Hero_Bullet(Hero* hero, Bullet* bullet);
    void ConEve_Treasure_Bullet(Treasure* treasure, Bullet* bullet);
    void ConEve_Hero_Diamond(Hero* hero, Diamond* dia);
    void ConEveBe_Hero_Smoke(Hero* hero, Smoke* smoke);
    void ConEveEnd_Hero_Smoke(Hero* hero, Smoke* smoke);
    void createSmoke(float dlt);
    void ConEve_Hero_Spell(Hero* hero, Bullet* spell);
    Hero* chooseHero(int choose,Hero* _hero);                      //选择英雄的函数
    void ButtonEvent(cocos2d::Ref* pSender, Scene* scene);
private:
    LoadingBar* BloodBar;
    LoadingBar* BlueBar;
    cocos2d::TMXTiledMap* m_map;
    Hero* m_hero;
    Vector<Hero*> ais;                                  //存放ai的数组
    ContactEvents ConEve;
    bool isConEve = false;
    std::vector<Smoke*> smoke_vec;
    int smoke_range = 8;
    int smoke_index = 0;
    Label* label;
    Label* label2;
    int Num;
};

#endif 