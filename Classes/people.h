/*people�࣬�̳о����࣬���Խ����ƶ�*/

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
    //�󶨾���
    void bindSprite(cocos2d::Sprite* sprite);

    //�õ�Ŀǰ����ֵ
    double getHP() const { return _HP; };

    //�õ�ĿǰATK
    double getATK()const { return _ATK; };

    //�趨����ֵ
    void setHP(double HP) { _HP = HP; };

    //�趨������
    void setATK(double ATK) { _ATK = ATK; };

    //�����ƶ�
    void move_L();

    //�����ƶ�
    void move_R();

    //�����ƶ�
    void move_U();

    //�����ƶ�
    void move_D();

    //����
    void move_LU();

    //����
    void move_LD();

    //����
    void move_RU();

    //����
    void move_RD();


public:
    double _HP;
    double _ATK;
    cocos2d::Sprite* m_hero;
};

#endif