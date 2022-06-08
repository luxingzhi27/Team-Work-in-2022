#include "MyBar.h"


bool MyBar::init()
{
	if (!Layer::init())
		return false;
	//����һ��������
	_bar = LoadingBar::create();
	//��������λ��
	_bar->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));
	//���ؽ�����ͼƬ
	_bar->loadTexture("BloodBar.png");
	_bar->setScaleX(_oriValue);
	_bar->setScale(0.3, 0.35);
	//���ó�ʼ�ٷֱ�
	_bar->setPercent(100);
	//���ý���������
	_bar->setDirection(ui::LoadingBar::Direction::LEFT);
	//���ý�������Ӣ�۵�λ��
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