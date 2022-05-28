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

    //������ʽ
    virtual void attack(cocos2d::Vec2 target);

    //�ܵ��˺�
    virtual void getHurt(Hero& enemy);

    //����ӵ�
    void fillProjectile();

    //��������
    void fillEnergy();

    //���⼼��
    void specialAttack(cocos2d::Vec2 target);

    //����
    void levelUp();

    // implement the "static create()" method manually
    CREATE_FUNC(Hero);

public:
    int projectileNum=MAX_PROJECTILE;    //���ڴ���ӵ�������
    int energy = 0;            //����ֵ
    cocos2d::Sprite* Projectile;    //������ӵ�
    cocos2d::Sprite* Blast;          //���⼼��
};

#endif