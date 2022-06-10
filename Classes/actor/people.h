/*people�࣬�̳о�����*/
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

    //�õ�Ŀǰ����ֵ
    double getHP() const { return _HP; };

    //�õ�ĿǰATK
    double getATK()const { return _ATK; };

    bool isAlive()const;

    //�趨����ֵ
    void setHP(int HP) { _HP = HP; };

    //�趨������
    void setATK(int ATK) { _ATK = ATK; }

    void setReach(int Reach) { _Reach = Reach; }

    void setSpeed(float Speed) { _Speed = Speed; }

    int getMaxHP();


protected:
    int _HP;
    int InitHP;  //����1��ʱ��HP
    int MaxCurrentHP;//HP����
    int _ATK;
    int InitATK;     //����1��ʱ��ATK
    int _Reach;  //�ӵ����
    float _Speed;//�ӵ��ķ����ٶ�
    bool _isAlive;
};

#endif