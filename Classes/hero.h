#ifndef __HERO_H__
#define __HERO_H__
#define LEVEL_UP_ATK 400
#define LEVEL_UP_HP 2000
#define MAX_PROJECTILE 6
#define MAX_ENERGY 4

#include "cocos2d.h"
#include"people.h"

class Hero : public People
{
public:
    Hero(double ATK = 400, double HP = 2000) :People(ATK, HP) {};
    virtual ~Hero();

    //攻击方式
    virtual void attack(cocos2d::Vec2 target);

    //受到伤害
    virtual void getHurt(Hero& enemy);

    //填充子弹
    void fillProjectile();

    //增加能量
    void fillEnergy();

    //特殊技能
    void specialAttack(cocos2d::Vec2 target);

    //升级
    void levelUp();

    // implement the "static create()" method manually
    CREATE_FUNC(Hero);

public:
    int projectileNum=MAX_PROJECTILE;    //用于存放子弹的数量
    int energy = 0;            //能量值
    cocos2d::Sprite* Projectile;    //发射的子弹
    cocos2d::Sprite* Blast;          //特殊技能
};

#endif