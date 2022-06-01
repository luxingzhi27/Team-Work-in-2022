#pragma once
#ifndef __HERO_H__
#define __HERO_H__

#define LEVEL_UP_ATK 400
#define LEVEL_UP_HP 2000
#define MAX_PROJECTILE 6
#define MAX_ENERGY 4

enum class HeroTowards{front,back,right,left};


#include"map"
#include"people.h"

class Hero : public People
{
public:
    Hero();
    virtual ~Hero();

    bool init();

    static Hero* create(const char* file);

    //������ʽ
    virtual void attack(cocos2d::Vec2 target);

    //�ܵ��˺�
    virtual void getHurt(Hero& enemy);

    //����ӵ�
    void fillProjectile();

    //��������
    void fillEnergy();

    //���⼼��
    virtual void specialAttack(cocos2d::Vec2 target);

    //����
    void levelUp();

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
    
    // implement the "static create()" method manually
    CREATE_FUNC(Hero);

protected:
    int projectileNum=MAX_PROJECTILE;    //���ڴ���ӵ�������
    int energy = 0;            //����ֵ
    cocos2d::Sprite* Projectile;    //������ӵ�
    cocos2d::Sprite* Blast;          //���⼼��
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

    

public:
    std::map<cocos2d::EventKeyboard::KeyCode, bool>  keys;
};

#endif