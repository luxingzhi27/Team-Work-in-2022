#pragma once
#ifndef __HERO_H__
#define __HERO_H__

#include"const/const.h"
#include"map"
#include"people.h"
#include"Article/Bullet.h"
#include<cmath>

class Bullet;


class Hero : public People
{
public:
    Hero();
    virtual ~Hero();

    bool init();

    static Hero* create(const char* file);

    //����ӵ�
    void fillBullet();

    //��������
    void fillEnergy();

    ////���⼼��
    //virtual void specialAttack(cocos2d::Vec2 target);


    void bindBullet(const char* bulletType);

    //����(��ñ�ʯ)
    void getDiamond();

    //update����
    void update(float dlt);

    //�ж�ĳ�������Ƿ���
    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);

    //�ƶ�ʱ����Ӧ��ִ�еĶ���
    void keyPressedDuration(cocos2d::EventKeyboard::KeyCode keycode);

    //��Ƭ��ͼ��������������ת��
    cocos2d::Vec2 Vec2toTile(cocos2d::Vec2 position);

    //�󶨵�ͼ
    void bindMap(cocos2d::TMXTiledMap* map);

    //Ӣ���ƶ�����
    void moveAnimation();

    bool isStatusChanged();

    int getDiamondNum();


    // implement the "static create()" method manually
    CREATE_FUNC(Hero);



protected:
    int energy = 0;            //����ֵ
    int Max_energy;
    //cocos2d::Sprite* Projectile;    //������ӵ�
    //cocos2d::Sprite* Blast;          //���⼼��
    cocos2d::TMXTiledMap* _map;
    cocos2d::Animate* m_front;          //��ǰ�߶���
    cocos2d::Animate* m_back;           //����߶���
    cocos2d::Animate* m_right;          //�����߶���
    cocos2d::Animate* m_left;           //�����߶���
    cocos2d::Animate* m_idle_front;
    cocos2d::Animate* m_idle_back;
    cocos2d::Animate* m_idle_left;
    cocos2d::Animate* m_idle_right;
    cocos2d::Animate* now;
    HeroTowards towards;
    HeroTowards lastTowards;
    bool isIdle;
    bool lastisIdle;
    bool isTouched = false;
    Bullet* _bullet;
    int bulletNum = MAX_BULLET_NUM;    //���ڴ���ӵ�������
    const char* BulletType;
    int diamondNum = 1;                //��ǰ���б�ʯ��

public:
    std::map<cocos2d::EventKeyboard::KeyCode, bool>  keys;
};

#endif