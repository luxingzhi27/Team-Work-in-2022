#pragma once
#ifndef __Game_SCENE_H__
#define __Game_SCENE_H__

#include "cocos2d.h"
using namespace std;

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void menuItemCallback(cocos2d::Ref* pSender, std::string eventname);
    /*void menuItemCallBack(Ref* sender);*/
    int musicID;
    CREATE_FUNC(GameScene);
};

#endif 