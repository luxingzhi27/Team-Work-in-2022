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

	//创建精灵
	auto _sprite = Sprite::create("timg2.png");
	this->addChild(_sprite);
	_sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_sprite->setPosition(Director::getInstance()->getVisibleSize() / 2);
	_sprite->setScale(0.6f);

	////创建进度条
	bar = LoadingBar::create();

	//锚点
	bar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	//将坐标设为中心
	bar->setPosition(visible / 2);
	this->addChild(bar);

	//进度条从左开始
	bar->setDirection(LoadingBar::Direction::LEFT);

	//加载进度条资源
	bar->loadTexture("bar.png");

	//设置初始化血量也就是百分比
	bar->setPercent(100);

	//设置显示比例
	bar->setScale(0.2);

	////创建对应的button按钮
	auto button = Button::create("attack.png", "attack.png", "attack.png");
	this->addChild(button);

	//设置按钮锚点
	button->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);

	//提取宽度进行坐标设置
	auto size = visible.width;
	button->setPositionX(size);
	button->setPositionY(0);

	//设置显示比例
	button->setScale(0.5);

	//添加按钮事件，按一下进行扣血
	button->addTouchEventListener([&](Ref* ref, ui::Widget::TouchEventType type)
		{
			//假如类型是按下时，那么血条减10
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				if (bar->getPercent() <= 0) //前体是还有血
				{
					auto button = dynamic_cast<Button*>(ref);  //转换类型
					button->setEnabled(false);                //设置权限
					return;
				}

				bar->setPercent(bar->getPercent() - 10);  //进行扣血

			}
		});

}

void MyButton::ComeBack(Ref* temp) //回调函数
{
	Director::getInstance()->end();//场景推出
}