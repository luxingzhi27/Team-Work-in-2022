#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"
#include "AudioEngine.h"
#include "ChooseScene/HeroChoose.h"
#include "ChooseScene/MapChoose.h"
using namespace cocos2d;
using namespace ui;
typedef void (*pFunc)(Ref*, Widget::TouchEventType);
typedef void (*pFunc2)(Ref*, ui::CheckBox::EventType type);
Button* Button_Create(std::string titleText, pFunc Event);
Button* Close_create(pFunc Event);
static int MapNum = 0;
static int HeroNum = 0;
void BarPercentUpdate(LoadingBar* bar, int damage, double MaxHP);
void BarPercentUpdate2(LoadingBar* bar, double CurrentHP, double MaxHP);
LoadingBar* BarCreate(Vec2 position, std::string filename);
MenuItemImage* MenuImageCreate();
Menu* MenuCreate(std::string filename, MenuItemImage* menuImage, Vec2 position);
ProgressTimer* ProgressCreate(int Tag, std::string filename, Vec2 position);