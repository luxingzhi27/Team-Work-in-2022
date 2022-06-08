#ifndef _CONTROLSRTTINGSCENE_
#define _CONTROLSRTTINGSCENE_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"
#include"Start/StartScene.h"
#include "SettingandCreating/FastCreating.h"
using namespace CocosDenshion;
using namespace cocos2d;
using namespace ui;

class SettingScene : public Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void buttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	CREATE_FUNC(SettingScene);

};
#endif

