/*people类，继承精灵类*/
#pragma once
#ifndef __PEOPLE_H__
#define __PEOPLE_H__
#include"const/const.h"
#include "cocos2d.h"
#include"Bar/Mybar.h"


#define MOVEDURATION 0.01
#define DISTANCE 1
#define UP Vec2(0,DISTANCE)
#define DOWN Vec2(0,-DISTANCE)
#define LEFT Vec2(-DISTANCE,0)
#define RIGHT Vec2(DISTANCE,0)


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

    bool isAlive()const;

    //设定生命值
    void setHP(int HP) { _HP = HP; };

    //设定攻击力
    void setATK(int ATK) { _ATK = ATK; }

    void setReach(int Reach) { _Reach = Reach; }

    void setSpeed(float Speed) { _Speed = Speed; }

    int getMaxHP();


protected:
    int _HP;
    int InitHP;  //人物1级时的HP
    int MaxCurrentHP;//HP上限
    int _ATK;
    int InitATK;     //人物1级时的ATK
    int _Reach;  //子弹射程
    float _Speed;//子弹的飞行速度
    bool _isAlive;
};

#endif