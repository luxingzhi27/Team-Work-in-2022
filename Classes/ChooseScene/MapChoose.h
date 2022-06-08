#pragma once
#ifndef _MapChooseScene_
#define _MapChooseScene_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;
#define MapNUM 4
class MapChoose : public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(MapChoose);
	CheckBox* MapBox[MapNUM];
	static int NumofChoseMap;
};

#endif