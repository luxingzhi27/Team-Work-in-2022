/*people�࣬�̳о�����*/
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

    //�õ�Ŀǰ����ֵ
    double getHP() const { return _HP; };

    //�õ�ĿǰATK
    double getATK()const { return _ATK; };

    //�趨����ֵ
    void setHP(double HP) { _HP = HP; };

    //�趨������
    void setATK(double ATK) { _ATK = ATK; };


protected:
    double _HP;
    double _ATK;
};

#endif