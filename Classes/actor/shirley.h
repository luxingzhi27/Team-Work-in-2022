#pragma once
#ifndef __SHIRLEY_H__
#define __SHIRLEY_H__

#include"cocos2d.h"
#include"const/const.h"
#include"hero.h"

 class Shirley : public Hero 
{
public:
    Shirley();
    virtual ~Shirley();

    bool init();

    static Shirley* create(const char* file);

    bool bindPhysicsBody();

    //¹¥»÷·½Ê½
    virtual void attack(Vec2 target);

    void onMouseDown(Event* event);

    virtual void specialAttack(cocos2d::Vec2 target);

    CREATE_FUNC(Shirley);

};

#endif