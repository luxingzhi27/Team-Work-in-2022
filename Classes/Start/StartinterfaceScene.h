
#ifndef __Startinterface_SCENE_H__
#define __Startinterface_SCENE_H__

#include "cocos2d.h"
#include "StartScene.h" 
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
class Startinterface : public cocos2d::Scene
{
public:
    void AlterToStartScene(float fl);//�����л����� ����Ҫһ������

    virtual bool init();
    CREATE_FUNC(Startinterface);
    void PlayMusic(float f1);
};

#endif 
