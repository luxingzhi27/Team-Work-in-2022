#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

#include"cocos2d.h"
#include"const/const.h"
#include"actor/hero.h"
USING_NS_CC;

class Hero;

class Bullet :public Sprite
{
public:
	Bullet();
	virtual ~Bullet();
	static Bullet* create(const char* filename, int tag = BULLET_TAG);
	bool init(int tag=BULLET_TAG);
	void setAttributes(int atk,int reach,float speed);

	int getATK()const;
	int getReach()const;
	float getSpeed()const;
	void setType(const char* filename);
	void onHit();//子弹命中时产生特效
	void fillenergy();
	void bindPhysicsbody(int tag = BULLET_TAG);
	void bindHero(Hero* hero);

	void update(float dlt);
	Hero* getHero()const;

	//void update(float dlt);
	//Vec2 Vec2toTile(Vec2 position);
private:
	int _ATK=0;
	int _Reach = 0;
	float _FlyingSpeed = 0.0;
	const char* _Type;
	Hero* _hero=nullptr;
};


#endif

