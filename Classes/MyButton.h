#pragma once
#include <cocos2d.h>
using namespace cocos2d;

#include "spine/spine.h"
#include "spine/spine-cocos2dx.h"
#include "../cocos2d/cocos/ui/UILoadingBar.h"  // ��ȡ��������
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
	LoadingBar* bar;  //��������ʾѪ��
};