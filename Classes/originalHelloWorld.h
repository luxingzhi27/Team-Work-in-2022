#pragma once
#ifndef __originalHelloWorld_SCENE_H__
#define __originalHelloWorld_SCENE_H__

#include "cocos2d.h"

class originalHelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender,int myevent);

    // implement the "static create()" method manually
    CREATE_FUNC(originalHelloWorld);
};

#endif // __originalHelloWorld_SCENE_H__
