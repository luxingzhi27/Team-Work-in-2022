#include "MyButton.h"

Scene* MyButton::createscene()
{
	return MyButton::create();
}

bool MyButton::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visible = Director::getInstance()->getVisibleSize();

	//��������
	auto _sprite = Sprite::create("timg2.png");
	this->addChild(_sprite);
	_sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_sprite->setPosition(Director::getInstance()->getVisibleSize() / 2);
	_sprite->setScale(0.6f);

	////����������
	bar = LoadingBar::create();

	//ê��
	bar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	//��������Ϊ����
	bar->setPosition(visible / 2);
	this->addChild(bar);

	//����������ʼ
	bar->setDirection(LoadingBar::Direction::LEFT);

	//���ؽ�������Դ
	bar->loadTexture("bar.png");

	//���ó�ʼ��Ѫ��Ҳ���ǰٷֱ�
	bar->setPercent(100);

	//������ʾ����
	bar->setScale(0.2);

	////������Ӧ��button��ť
	auto button = Button::create("attack.png", "attack.png", "attack.png");
	this->addChild(button);

	//���ð�ťê��
	button->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);

	//��ȡ��Ƚ�����������
	auto size = visible.width;
	button->setPositionX(size);
	button->setPositionY(0);

	//������ʾ����
	button->setScale(0.5);

	//��Ӱ�ť�¼�����һ�½��п�Ѫ
	button->addTouchEventListener([&](Ref* ref, ui::Widget::TouchEventType type)
		{
			//���������ǰ���ʱ����ôѪ����10
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				if (bar->getPercent() <= 0) //ǰ���ǻ���Ѫ
				{
					auto button = dynamic_cast<Button*>(ref);  //ת������
					button->setEnabled(false);                //����Ȩ��
					return;
				}

				bar->setPercent(bar->getPercent() - 10);  //���п�Ѫ

			}
		});

}

void MyButton::ComeBack(Ref* temp) //�ص�����
{
	Director::getInstance()->end();//�����Ƴ�
}