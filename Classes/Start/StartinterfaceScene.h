
#ifndef __Startinterface_SCENE_H__
#define __Startinterface_SCENE_H__

#include "cocos2d.h"

class Startinterface : public cocos2d::Scene
{
public:
    void AlterToStartScene(float fl);//�����л����� ����Ҫһ������
    virtual bool init();
    CREATE_FUNC(Startinterface);

};

#endif 
