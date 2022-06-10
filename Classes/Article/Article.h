#pragma once
/*****
* @file Article
* @brief ��Ʒ�࣬���������뱦ʯ
******/
#ifndef _ARTICLE_H_
#define _ARTICLE_H_

#include"cocos2d.h"
#include"const/const.h"
#include "SettingandCreating/FastCreating.h"
USING_NS_CC;




/***
*brief ����
*/
class Treasure :public Sprite
{
public:
	Treasure();
	virtual ~Treasure();
	static Treasure* create(const char* filename);
	bool init();
	int getHP()const;
	void getHurt(int hurt);
	void getDestroyed();
	void createDiamond();
	void bindPhysicsBody();
	bool isDestroyed();
private:
	int _HP=TreasureHP;
	bool _isDestroyed = false;
	LoadingBar* BloodBar;
};

/////////////////////////////////

class Diamond :public Sprite
{
public:
	Diamond();
	virtual ~Diamond();
	static Diamond* create(const char* filename);
	bool init();
	void run_action();
	/*void setPosition(Vec2 Pos);*/
	void bindPhysicsBody();
private:
	Sequence* _Appear;
	RepeatForever* _Shining;
	void setAppear();
	void setShining();
	TMXTiledMap* _map;
	bool isCreated;
};


#endif // !_ARTICLE_H_
