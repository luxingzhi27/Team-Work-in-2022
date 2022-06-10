#pragma once
#ifndef __HERO_H__
#define __HERO_H__

#include"const/const.h"
#include"map"
#include"people.h"
#include"Article/Article.h"
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

    //填充子弹
    void fillBullet(float dt);

    //随时间恢复血量
    void fillHP(float dt);

    //增加能量
    void fillEnergy();

    ////特殊技能
    //virtual void specialAttack(cocos2d::Vec2 target);


    void bindBullet(const char* bulletType);
    void bindSpell(const char* spelltype);

    //升级(获得宝石)
    void getDiamond();

    //update函数
    void update(float dlt);

    //判断某个按键是否按下
    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);

    //移动时精灵应该执行的动作
    void keyPressedDuration(cocos2d::EventKeyboard::KeyCode keycode);

    //瓦片地图坐标与向量坐标转换
    cocos2d::Vec2 Vec2toTile(cocos2d::Vec2 position);

    //绑定地图
    void bindMap(cocos2d::TMXTiledMap* map);

    //英雄移动动画
    void moveAnimation();

    bool isStatusChanged();

    int getDiamondNum();

    //草丛中隐身
    void grassInvisible();

    cocos2d::Vec2 aiSearch(int &aitype);             //ai寻找周围的宝箱钻石或英雄

    void aiMove();


    virtual void attack(Vec2 target);
    virtual void specialAttack(cocos2d::Vec2 target);

    void setai();

    bool isAI()const;

    int getEnergy()const;

    bool isPoisoning()const;

    void getPoisoning(float rate);

    void setPoisoning(bool flag);


    void getHurt(int hurt);

    void die();

    void createDiamond();

    void outofFighting(float dlt);//脱战

    int getBulletNum();

    CREATE_FUNC(Hero);



protected:
    int energy = 0;            //能量值
    int Max_energy;
    //cocos2d::Sprite* Projectile;    //发射的子弹
    //cocos2d::Sprite* Blast;          //特殊技能
    cocos2d::TMXTiledMap* _map;
    cocos2d::Animate* m_front;          //向前走动画
    cocos2d::Animate* m_back;           //向后走动画
    cocos2d::Animate* m_right;          //向右走动画
    cocos2d::Animate* m_left;           //向左走动画
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
    Bullet* _spell;
    int bulletNum = MAX_BULLET_NUM;    //用于存放子弹的数量
    const char* BulletType;
    const char* SpellType;
    int diamondNum = 1;                //当前持有宝石数
    bool isai = false;
    bool isFirst = true;
    int _isPoisoning = 0;                 //中毒状态
    int _isfighting = 0;             //脱战状态
public:
    std::map<cocos2d::EventKeyboard::KeyCode, bool>  keys;
};

#endif