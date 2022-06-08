#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"
#include "AudioEngine.h"
#include "HeroChoose.h"
#include "MapChoose.h"
using namespace cocos2d;
using namespace ui;
typedef void (*pFunc)(Ref*, Widget::TouchEventType);
typedef void (*pFunc2)(Ref*, ui::CheckBox::EventType type);
Button* Button_Create(std::string titleText, pFunc Event);
Button* Close_create(pFunc Event);
static int MapNum = 0;
static int HeroNum = 0;