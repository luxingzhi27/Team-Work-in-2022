#include "MyBar.h"

Layer* MyBar::createLayer(std::string _BarPictureFileName, Sprite* _MySprite)
{
	auto mybar = MyBar::create();
	mybar->_bar = LoadingBar::create();

	//进度条的位置
	mybar->_bar->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));
	//加载进度条图片
	mybar->_bar->loadTexture(_BarPictureFileName);
	mybar->_bar->setScaleX(mybar->_oriValue);
	mybar->_bar->setScale(0.3, 0.35);
	//设置初始百分比
	mybar->_bar->setPercent(100);
	//设置进度条朝向
	mybar->_bar->setDirection(ui::LoadingBar::Direction::LEFT);
	//设置进度条与英雄的位置
	mybar->_bar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_MySprite->addChild(mybar->_bar);
	mybar->_bar->setPosition(Vec2(15, 55));
	return mybar;
}

bool MyBar::init()
{
	if (!Layer::init())
		return false;
	//创建一个进度条
	return true;
}
//update MyBar
bool MyBar::BarPercentUpdate(int damage)
{
	if (_bar->getPercent() >= 0)
		_bar->setPercent(_bar->getPercent() - damage / _oriValue);
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