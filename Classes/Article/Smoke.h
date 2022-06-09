#pragma once
#ifndef _SMOKE_H_
#define _SMOKE_H_

#include"cocos2d.h"
#include"const/const.h"
USING_NS_CC;

class Smoke :public Sprite
{
public:
	Smoke();
	~Smoke();
	static Smoke* create(const char* filename);
	bool init();
	void bindPhysicsBody();
	void RunfadeIn();
private:
	FadeIn* _fadein;
};

#endif