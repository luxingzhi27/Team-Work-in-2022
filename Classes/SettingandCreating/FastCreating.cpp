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
	p = Button::create("ButtonU.png", "ButtonS.png");
	p->setScale(0.9,0.75);
	p->setTitleText(titleText);
	p->setTitleColor(Color3B::WHITE);
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

LoadingBar* BarCreate(Vec2 position, std::string filename)
{

	//创建一个进度条
	auto _bar = LoadingBar::create();
	//加载进度条图片
	_bar->loadTexture(filename);
	_bar->setScale(0.3, 0.35);
	//设置初始百分比
	_bar->setPercent(100);
	//设置进度条朝向
	_bar->setDirection(ui::LoadingBar::Direction::LEFT);
	//设置进度条与英雄的位置
	_bar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_bar->setPosition(position);
	return _bar;
}
void BarPercentUpdate(LoadingBar* bar, int damage, double MaxHP)
{
	if (bar->getPercent() >= 0)
		bar->setPercent(bar->getPercent() - double(damage) / MaxHP * 100);
	//auto button = dynamic_cast<Button*>(ref);

}

MenuItemImage* MenuImageCreate()
{
	auto menuImage = MenuItemImage::create("ButtonU.png", "ButtonS.png");
	//menuImage->setScale(0.8, 0.4);
	return menuImage;
}
Menu* MenuCreate(std::string filename, MenuItemImage* menuImage,Vec2 position) {

	//菜单字体
	auto label = Label::createWithTTF(filename, "fonts/Marker Felt.ttf", 30);
	auto menuItem = MenuItemLabel::create(label);
	menuItem->setColor(Color3B::GRAY);
	menuItem->setScale(2);
	//距离菜单的位置
	menuItem->setPosition(position);
	menuImage->setPosition(position);
	menuImage->setScale(menuItem->getContentSize().width / menuImage->getContentSize().width * 2.5f,
		menuItem->getContentSize().height / menuImage->getContentSize().height*2.8f);
	Menu* pMenu = Menu::create(menuImage, menuItem, NULL);
	pMenu->setPosition(0,0);
	return pMenu;
	
}
ProgressTimer* ProgressCreate(int Tag,std::string filename, Vec2 position)
{
	auto sprBlood = Sprite::create(filename);  //创建血条
	ProgressTimer* progress = ProgressTimer::create(sprBlood); //创建progress对象
	progress->setType(ProgressTimer::Type::BAR);        //类型：条状
	progress->setPosition(position);
	progress->setScale(0.3, 0.35);
	//从右到左减少血量
	progress->setMidpoint(Point(0, 0.5));     //如果是从左到右的话，改成(1,0.5)即可
	progress->setBarChangeRate(Point(1, 0));
	progress->setTag(Tag);          //做一个标记
	return progress;
}
Label* LabelCreate(std::string Text) {
	auto label = Label::createWithTTF(Text, "fonts/Marker Felt.ttf", 40);
	label->setTextColor(Color4B::ORANGE);
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	label->setScaleX(1.35f);
	label->enableShadow();
	return label;
}