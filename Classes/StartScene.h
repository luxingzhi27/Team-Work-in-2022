#ifndef _STARTSCENE_
#define _STARTSCENE_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"
#include "AudioEngine.h"
using namespace cocos2d;
using namespace ui;
typedef void (*pFunc)(Ref*, Widget::TouchEventType);

class StartScene : public Scene
{
private:
	Size visibleSize;
	Vec2 origin;
	void Button_Add(std::vector<Button*> buttonList);//°´Å¥Ìí¼Óº¯Êý
public:
	StartScene();
	virtual bool init();
	CREATE_FUNC(StartScene);
};

#endif



