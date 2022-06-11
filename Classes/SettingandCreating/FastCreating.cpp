#include "FastCreating.h"

//����һ�����ı��İ�ť���¼������Լ�����
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


//�����˳���ť
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

	//����һ��������
	auto _bar = LoadingBar::create();
	//���ؽ�����ͼƬ
	_bar->loadTexture(filename);
	_bar->setScale(0.3, 0.35);
	//���ó�ʼ�ٷֱ�
	_bar->setPercent(100);
	//���ý���������
	_bar->setDirection(ui::LoadingBar::Direction::LEFT);
	//���ý�������Ӣ�۵�λ��
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

	//�˵�����
	auto label = Label::createWithTTF(filename, "fonts/Marker Felt.ttf", 30);
	auto menuItem = MenuItemLabel::create(label);
	menuItem->setColor(Color3B::GRAY);
	menuItem->setScale(2);
	//����˵���λ��
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
	auto sprBlood = Sprite::create(filename);  //����Ѫ��
	ProgressTimer* progress = ProgressTimer::create(sprBlood); //����progress����
	progress->setType(ProgressTimer::Type::BAR);        //���ͣ���״
	progress->setPosition(position);
	progress->setScale(0.3, 0.35);
	//���ҵ������Ѫ��
	progress->setMidpoint(Point(0, 0.5));     //����Ǵ����ҵĻ����ĳ�(1,0.5)����
	progress->setBarChangeRate(Point(1, 0));
	progress->setTag(Tag);          //��һ�����
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