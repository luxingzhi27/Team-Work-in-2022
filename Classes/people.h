/*people类，继承精灵类，可以进行移动*/

#ifndef __PEOPLE_H__
#define __PEOPLE_H__
#define START_ATK 400
#define START_HP 2000
#include "cocos2d.h"

class People : public cocos2d::Node
{
public:
    People(double ATK =START_ATK , double HP = START_HP) :_ATK(ATK), _HP(HP) {};
    virtual ~People();
    //绑定精灵
    void bindSprite(cocos2d::Sprite* sprite);

    //得到目前生命值
    double getHP() const { return _HP; };

    //得到目前ATK
    double getATK()const { return _ATK; };

    //设定生命值
    void setHP(double HP) { _HP = HP; };

    //设定攻击力
    void setATK(double ATK) { _ATK = ATK; };

    //向左移动
    void move_L();

    //向右移动
    void move_R();

    //向上移动
    void move_U();

    //向下移动
    void move_D();

    //左上
    void move_LU();

    //左下
    void move_LD();

    //右上
    void move_RU();

    //右下
    void move_RD();


public:
    double _HP;
    double _ATK;
    cocos2d::Sprite* m_hero;
};

#endif