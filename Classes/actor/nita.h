#pragma once
#ifndef __NITA_H__
#define __NITA_H__

#include"cocos2d.h"
#include"const/const.h"
#include"hero.h"

class Nita : public Hero
{
public:
    Nita();
    virtual ~Nita();

    bool init();

    static Nita* create(const char* file);

    bool bindPhysicsBody();

    //¹¥»÷·½Ê½
    virtual void attack(Vec2 target);

    void onMouseDown(Event* event);

    virtual void specialAttack(cocos2d::Vec2 target);

    CREATE_FUNC(Nita);

};

#endif
