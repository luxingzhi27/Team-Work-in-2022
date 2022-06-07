#include "MyBar.h"


bool MyBar::init()
{
	if (!Layer::init())
		return false;
	//创建一个进度条
	_bar = LoadingBar::create();
	//进度条的位置
	_bar->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));
	//加载进度条图片
	_bar->loadTexture("BloodBar.png");
	_bar->setScaleX(_oriValue);
	_bar->setScale(0.3, 0.35);
	//设置初始百分比
	_bar->setPercent(100);
	//设置进度条朝向
	_bar->setDirection(ui::LoadingBar::Direction::LEFT);
	//设置进度条与英雄的位置
	_bar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	addChild(_bar);
    _bar->setPosition(Vec2(15, 55));
	return true;
}
//update MyBar
bool MyBar::BarPercentUpdate(int damage,double HP)
{
	if (_bar->getPercent() >= 0)
		_bar->setPercent(_bar->getPercent() - damage/HP*100 );
	//auto button = dynamic_cast<Button*>(ref);
	if (_bar->getPercent() > 0)
		return true;
	else
		return false;
}

void MyBar::setOriValue(int originalvalue)
{
	_oriValue = originalvalue;
}