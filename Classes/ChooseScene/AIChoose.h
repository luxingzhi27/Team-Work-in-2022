#pragma once
#ifndef _AICHOOSE_
#define _AICHOOSE_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;
#define MAX_AI_NUM 9
class AIChoose : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(AIChoose);
	void menuItemCallback(cocos2d::Ref* pSender, std::string eventname);
private:
	int NumOfAI;
	Label* label2;
};

#endif