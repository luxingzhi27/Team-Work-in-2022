#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SettingandCreating/FastCreating.h"

class EndScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene(bool isVictory);
	virtual bool init();
	CREATE_FUNC(EndScene);
	bool GetEnd() { return isVictory; };
	void menuItemCallback(cocos2d::Ref* pSender, std::string eventname);
private:
	bool isVictory;  //≈–∂œ «∑Ò §¿˚

};