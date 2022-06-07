#include "MyBar.h"

Layer* MyBar::createLayer(std::string _BarPictureFileName, Sprite* _MySprite)
{
	auto mybar = MyBar::create();
	mybar->_bar = LoadingBar::create();

	//��������λ��
	mybar->_bar->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));
	//���ؽ�����ͼƬ
	mybar->_bar->loadTexture(_BarPictureFileName);
	mybar->_bar->setScaleX(mybar->_oriValue);
	mybar->_bar->setScale(0.3, 0.35);
	//���ó�ʼ�ٷֱ�
	mybar->_bar->setPercent(100);
	//���ý���������
	mybar->_bar->setDirection(ui::LoadingBar::Direction::LEFT);
	//���ý�������Ӣ�۵�λ��
	mybar->_bar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_MySprite->addChild(mybar->_bar);
	mybar->_bar->setPosition(Vec2(15, 55));
	return mybar;
}

bool MyBar::init()
{
	if (!Layer::init())
		return false;
	//����һ��������
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