#include "hero.h"
#include"cocos2d.h"
USING_NS_CC;

#include"windows.h"


Hero::~Hero()
{
}

void Hero::attack(Vec2 target)
{	
	if (projectileNum > 0)
	{
		Projectile = Sprite::create("projectile.png");
		this->addChild(Projectile);
		auto begin = this->getPosition();
		auto route = target - begin;
		route.normalize();
		route *= 1000;
		auto move = MoveTo::create(1.f, route);
		Projectile->runAction(move);

		//ÿһ�ι�������ʹ�ӵ���������
		projectileNum--;
	}
}

void Hero::getHurt(Hero& enemy)
{
	_HP -= enemy._ATK;
}

void Hero::fillProjectile()
{
	static int cnt = 0;
	cnt++;
	log("cnt=%d", cnt);
	if (projectileNum < 6&&cnt>120)  //ʵ����ʱ������Ч��
	{
		projectileNum++;
		cnt = 0;
	}
	if (cnt == 100000)
		cnt = 0;
}

void Hero::fillEnergy()
{
	if (energy < 6)
		energy++;
}

void Hero::specialAttack(Vec2 target)
{
	if (energy == MAX_ENERGY)
	{
		Blast = Sprite::create("blast.png");
		this->addChild(Blast);
		Blast->setRotation(180);
		Blast->setScale(0.2);
		auto begin = this->getPosition();
		auto route = target - begin;
		route.normalize();
		auto Angle = route.angle(Vec2(1, 0),route);     //�õ����䷽����������ʼ����н�
		Angle = Angle / 3.14159 * 180;           //ת���ɽǶ�
		Blast->setRotation(Angle);
		route *= 1000;
		auto move = MoveTo::create(1.f, route);
		Blast->runAction(move);
		log("successfully shoot");
		if ((int)Blast->getPosition().getLength()==1000)
			removeChild(Blast);

		energy = 0;        //������� 
	}
}

void Hero::levelUp()
{
	_ATK += LEVEL_UP_ATK;
	_HP += LEVEL_UP_HP;
}
