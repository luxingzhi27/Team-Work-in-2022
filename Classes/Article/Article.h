#pragma once
/*****
* @file Article
* @brief 物品类，包括宝箱与宝石
******/
#ifndef _ARTICLE_H_
#define _ARTICLE_H_

#include"cocos2d.h"
#include"const/const.h"
#include"Mybar.h"
USING_NS_CC;




/***
*brief 宝箱
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
	TMXTiledMap* _map;
	bool _isDestroyed = false;
	MyBar* bar;
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
	void setPosition(Vec2 Pos);
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
