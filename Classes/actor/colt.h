#pragma once
#ifndef __COLT_H__
#define __COLT_H__

#include"cocos2d.h"
#include"const/const.h"
#include"hero.h"

class Colt : public Hero
{
public:
    Colt();
    virtual ~Colt();

    bool init();

    static Colt* create(const char* file);


    //¹¥»÷·½Ê½
    virtual void attack(Vec2 target);

    void onMouseDown(Event* event);

    virtual void specialAttack(cocos2d::Vec2 target);

    CREATE_FUNC(Colt);

};

#endif
