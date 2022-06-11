#pragma once
#include "cocos2d.h"
USING_NS_CC;

#include "ui/CocosGUI.h"
#include "SettingandCreating/FastCreating.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"
#include"Start/StartScene.h"
using namespace CocosDenshion;
class HelpLayer :public Layer
{
public:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	virtual bool init();
	CREATE_FUNC(HelpLayer);
	void menuItemCallback(cocos2d::Ref* pSender, std::string eventname);
	void menuItemCallback2(cocos2d::Ref* pSender, std::string eventname);
	static cocos2d::Layer* createLayer(std::string Choose);
};