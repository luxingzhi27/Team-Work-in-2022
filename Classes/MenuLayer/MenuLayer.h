#pragma once
#include "cocos2d.h"
USING_NS_CC;

#include "ui/CocosGUI.h"
#include "SettingandCreating/FastCreating.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"
#include"Start/StartScene.h"
#include "ChooseScene/HeroChoose.h"
using namespace CocosDenshion;
class MenuLayer :public Layer
{
public:

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	virtual bool init();
	CREATE_FUNC(MenuLayer);
	void AddMenu(std::vector<MenuItemFont*> MenuItemFontList);
	void menuItemCallback(cocos2d::Ref* pSender, std::string eventname);
};