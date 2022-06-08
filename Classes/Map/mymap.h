#pragma once
#ifndef __MAP_LAYER_H__
#define __MAP_LAYER_H__


#include"actor/shirley.h"
#include"const/const.h"
#include"actor/hero.h"
#include"Article/Article.h"
#include"Article/Bullet.h"
class MapLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createMapScene();
    virtual bool init();
    cocos2d::TMXTiledMap* getMap() const;
    void update(float dlt);
    CREATE_FUNC(MapLayer);
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void ConEve_Hero_Bullet(Hero* hero, Bullet* bullet);
    void ConEve_Treasure_Bullet(Treasure* treasure, Bullet* bullet);
    void ConEve_Hero_Diamond(Hero* hero, Diamond* dia);
private:
    cocos2d::TMXTiledMap* m_map;
    Shirley* m_hero;
    ContactEvents ConEve;
    bool isConEve = false;
};

#endif 