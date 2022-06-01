#pragma once
#ifndef __SHIRLEY_H__
#define __SHIRLEY_H__

#include"cocos2d.h"
#include"hero.h"

 class Shirley : public Hero 
{
public:
    Shirley();
    virtual ~Shirley();

    bool init();

    static Shirley* create(const char* file);

    //������ʽ
    void attack(cocos2d::Vec2 target);

    //�ܵ��˺�
    void getHurt(Hero& enemy);

    void specialAttack(cocos2d::Vec2 target);


    CREATE_FUNC(Shirley);

};

#endif