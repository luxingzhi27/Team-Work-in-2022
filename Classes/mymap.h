#pragma once
#ifndef __MAP_LAYER_H__
#define __MAP_LAYER_H__


#include"actor/shirley.h"

class MapLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createMapScene();
    virtual bool init();
    cocos2d::TMXTiledMap* getMap() const;
    void update(float dlt);
    CREATE_FUNC(MapLayer);
private:
    cocos2d::TMXTiledMap* m_map;
    Shirley* m_hero;
};

#endif 