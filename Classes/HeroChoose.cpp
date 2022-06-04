#include "HeroChoose.h"
#include "FastCreating.h"
#include "MapChoose.h"
bool HeroChoose::init()
{
	if (!Scene::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//Sprite* myHero[5];
	//for (int i = 0; i < 5; i++)
	//{
	//	char imageName[15] = { 0 };
	//	sprintf(imageName, "myHero%d", i);
	//	myHero[i] = Sprite::create(imageName);
	//	myHero[i]->setPosition(visibleSize.width * (i + 1) / 6, visibleSize.height / 2);
	//	this->addChild(myHero[i], i);
	//}

	//创建一个提示文本
	auto label = Label::createWithTTF("Choose Your Hero", "fonts/Marker Felt.ttf", 58);
	label->setTextColor(Color4B::ORANGE);
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	label->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height);
	label->setScaleX(1.35f);
	label->enableShadow();
	this->addChild(label);

	//创建一个复选框
	for (int i = 0; i < HeroNUM; i++) 
	{
		HeroBox[i] = CheckBox::create("US.png", "US.png", "S.png", "US.png", "S.png");
		addChild(HeroBox[i]);
		HeroBox[i]->setScale(0.7);
		HeroBox[i]->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		HeroBox[i]->setPosition(Vec2(visibleSize.width * (i + 1) / (HeroNUM+1),visibleSize.height/3));
	}
	HeroBox[HeroNum]->setSelected(true);
	HeroBox[0]->addEventListener([&](Ref* ref, ui::CheckBox::EventType type)
		{
			if (type == CheckBox::EventType::SELECTED)
			{
				for (int m = 0; m < HeroNUM; m++)
				{
					if (HeroBox[m]->isSelected() && m != 0)
						HeroBox[m]->setSelected(false);
				}
				HeroNum = 0;
			}
		});
	HeroBox[1]->addEventListener([&](Ref* ref, ui::CheckBox::EventType type)
		{
			if (type == CheckBox::EventType::SELECTED)
			{
				for (int m = 0; m < HeroNUM; m++)
				{
					if (HeroBox[m]->isSelected() && m != 1)
						HeroBox[m]->setSelected(false);
				}
				HeroNum = 1;
			}
		});
	HeroBox[2]->addEventListener([&](Ref* ref, ui::CheckBox::EventType type)
		{
			if (type == CheckBox::EventType::SELECTED)
			{
				for (int m = 0; m < HeroNUM; m++)
				{
					if (HeroBox[m]->isSelected() && m != 2)
						HeroBox[m]->setSelected(false);
				}
				HeroNum = 2;
			}
		});
	HeroBox[3]->addEventListener([&](Ref* ref, ui::CheckBox::EventType type)
		{
			if (type == CheckBox::EventType::SELECTED)
			{
				for (int m = 0; m < HeroNUM; m++)
				{
					if (HeroBox[m]->isSelected() && m != 3)
						HeroBox[m]->setSelected(false);
				}
				HeroNum = 3;
			}
		});


	//创建一个返回按钮
	auto ReturnButton = Button_Create("Return", [](Ref* ref, Widget::TouchEventType type)
		{
			switch (type) {
			case Widget::TouchEventType::ENDED:
				Director::getInstance()->popScene();
				break;
			default:
				break;
			}
		});
	ReturnButton->setScale(0.7);
	ReturnButton->setPosition(Vec2(origin.x + ReturnButton->getContentSize().width, origin.y + ReturnButton->getContentSize().height/3));
	addChild(ReturnButton);

	//创建一个next按钮
	auto NextButton = Button_Create("Next", [](Ref* ref, Widget::TouchEventType type)
		{
			switch (type) {
			case Widget::TouchEventType::ENDED:
				Director::getInstance()->pushScene(MapChoose::create());
				break;
			default:
				break;
			}
		});
	NextButton->setScale(0.7);
	NextButton->setPosition(Vec2(visibleSize.width/1.5 + NextButton->getContentSize().width /2, origin.y + NextButton->getContentSize().height / 3));
	addChild(NextButton);


	//创建一个退出按钮
	auto ExitImage = Close_create([](Ref* ref, Widget::TouchEventType type)
		{
			switch (type) {
			case Widget::TouchEventType::ENDED:
				Director::getInstance()->end();
				break;
			default:
				break;
			}
		});
	addChild(ExitImage);

	return true;
}

