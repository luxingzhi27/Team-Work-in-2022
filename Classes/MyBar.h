#pragma once
#include "cocos2d.h"
USING_NS_CC;

#include "ui/CocosGUI.h"
using namespace ui;
class MyBar : public Layer
{
public:
	static Layer* createLayer(std::string _BarPictureFileName, Sprite* _MySprite);
	virtual bool init();
	CREATE_FUNC(MyBar);
	bool BarPercentUpdate(int damage);
	//you can set the original value from 1-10
	void setOriValue(int originalvalue);
	void SetBarPosition(int x,int y);
private:
	LoadingBar* _bar;
	int _oriValue = 1;
};

