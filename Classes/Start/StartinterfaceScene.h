
#ifndef __Startinterface_SCENE_H__
#define __Startinterface_SCENE_H__

#include "cocos2d.h"
#include "StartScene.h" 
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
class Startinterface : public cocos2d::Scene
{
public:
    void AlterToStartScene(float fl);//场景切换函数 ，需要一个参数

    virtual bool init();
    CREATE_FUNC(Startinterface);
    void PlayMusic(float f1);
};

#endif 
