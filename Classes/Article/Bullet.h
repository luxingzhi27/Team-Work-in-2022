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
	static Bullet* create(const char* filename);
	bool init();
	void setAttributes(int atk,int reach,float speed);
	int getATK();
	void setType(const char* filename);
	void onHit();//子弹命中时产生特效
	void fillenergy();
	void bindPhysicsbody();
	void bindHero(Hero* hero);
	//void update(float dlt);
	//Vec2 Vec2toTile(Vec2 position);
	void bindMap(TMXTiledMap* map);
private:
	int _ATK=0;
	int _Reach = 0;
	float _FlyingSpeed = 0;
	const char* _Type;
	Hero* _hero;
};


#endif

