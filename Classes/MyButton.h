#pragma once
#include <cocos2d.h>
using namespace cocos2d;

#include "spine/spine.h"
#include "spine/spine-cocos2dx.h"
#include "../cocos2d/cocos/ui/UILoadingBar.h"  // 读取进度条库
#include "ui/CocosGUI.h"
using namespace ui;

class MyButton : public Scene
{
public:
	static Scene* createscene();
	CREATE_FUNC(MyButton);
	virtual bool init();
	void ComeBack(Ref* temp);

private:
	LoadingBar* bar;  //进度条显示血量
};