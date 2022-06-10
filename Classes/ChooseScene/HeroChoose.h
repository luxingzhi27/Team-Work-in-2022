#pragma once
#ifndef _HeroChooseScene_
#define _HeroChooseScene_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Start/StartScene.h"
using namespace cocos2d;
using namespace ui;
#define HeroNUM 4
class HeroChoose : public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(HeroChoose);
	CheckBox* HeroBox[HeroNUM];
	void BoxListenerAdd(int num);
	int getHeroNum() { return ChHeroNum; };
private:
	int ChHeroNum;
};

#endif