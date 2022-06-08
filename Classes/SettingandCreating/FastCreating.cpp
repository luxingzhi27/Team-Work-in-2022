#include "FastCreating.h"

//创建一个含文本的按钮，事件可以自己定义
/*
	auto MyButton = Button_Create("Text", [](Ref* ref, Widget::TouchEventType type)
		{
			switch (type) {
			case Widget::TouchEventType::ENDED:
				Director::getInstance()->
				break;
			default:
				break;
			}
		});
*/
Button* Button_Create(std::string titleText, pFunc Event)
{
	Button* p = new(std::nothrow) Button;
	if (p == nullptr)
	{
		return nullptr;
	}
	p = Button::create("ButtonN.png", "ButtonS.png");
	p->setScale(1.6f, 0.8f);
	p->setTitleText(titleText);
	p->setTitleColor(Color3B::GRAY);
	p->setTitleFontName("fonts/Marker Felt.ttf");
	p->setTitleFontSize(40);
	p->addTouchEventListener(Event);
	return p;
}


//创建退出按钮
Button* Close_create(pFunc Event)
{
	Button* p = new(std::nothrow) Button;
	if (p == nullptr)
	{
		return nullptr;
	}
	p = Button::create("CloseNormal.png","CloseSelected.png");
	auto _visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 _origin = Director::getInstance()->getVisibleOrigin();
	p->setScale(2);
	float x = _origin.x + _visibleSize.width - p->getContentSize().width;
	float y = _origin.y + p->getContentSize().height;
	p->setPosition(Vec2(x, y));
	p->addTouchEventListener(Event);
	return p;
}

