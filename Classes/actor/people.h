/*people类，继承精灵类*/
#pragma once
#ifndef __PEOPLE_H__
#define __PEOPLE_H__
#define START_ATK 400
#define START_HP 2000

#include "cocos2d.h"

class People : public cocos2d::Sprite
{
public:
    People();
    virtual ~People();

    bool init();

    static People* create(const char* file);

    static cocos2d::Animate* getAnimate(const char* status, const char* heroName, int cnt, int loop);

    //得到目前生命值
    double getHP() const { return _HP; };

    //得到目前ATK
    double getATK()const { return _ATK; };

    //设定生命值
    void setHP(double HP) { _HP = HP; };

    //设定攻击力
    void setATK(double ATK) { _ATK = ATK; };


protected:
    double _HP;
    double _ATK;
};

#endif