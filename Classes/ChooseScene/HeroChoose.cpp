#include "HeroChoose.h"
#include "SettingandCreating/FastCreating.h"
#include "AIChoose.h"
#include"global.h"
bool HeroChoose::init()
{
	if (!Layer::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto bg = LayerColor::create(Color4B::GRAY);
	addChild(bg);
	Sprite* myHero[5];
	for (int i = 1; i < 5; i++)
	{
		std::string str = "animation/hero_";
		char ch = '0';
		ch += i;
		str += ch;
		str += ".png";
		myHero[i] = Sprite::create(str);
		myHero[i]->setScale(2.5);
		myHero[i]->setPosition(visibleSize.width * (i) / 5, visibleSize.height / 1.8);
		this->addChild(myHero[i]);
	}

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
	HeroBox[NumOfHero]->setSelected(true);
	HeroBox[0]->addEventListener([&](Ref* ref, ui::CheckBox::EventType type)
		{
			if (type == CheckBox::EventType::SELECTED)
			{
				for (int m = 0; m < HeroNUM; m++)
				{
					if (HeroBox[m]->isSelected() && m != 0)
						HeroBox[m]->setSelected(false);
				}
				//ChHeroNum = 0;
				NumOfHero = 0;
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
				ChHeroNum = 1;
				NumOfHero = 1;
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
				ChHeroNum = 2;
				NumOfHero = 2;
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
				ChHeroNum = 3;
				NumOfHero = 3;
			}
		});

	auto menuImage = MenuImageCreate();
	menuImage->setCallback(CC_CALLBACK_1(HeroChoose::menuItemCallback,
		this,
		"Return"));
	auto pMenu = MenuCreate("Return", menuImage,
		Vec2(visibleSize.width / 4, visibleSize.height / 7));
	addChild(pMenu);

	auto menuImage2 = MenuImageCreate();
	menuImage2->setCallback(CC_CALLBACK_1(HeroChoose::menuItemCallback,
		this,
		"Next"));
	auto pMenu2 = MenuCreate("Next", menuImage2,
		Vec2(visibleSize.width * 3 / 4, visibleSize.height / 7));
	addChild(pMenu2);


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

void HeroChoose::menuItemCallback(cocos2d::Ref* pSender, std::string eventname)
{
	auto layer = AIChoose::create();
	this->removeFromParentAndCleanup(true);
	if (eventname == "Return")
		Director::getInstance()->replaceScene(StartScene::create());
	if (eventname == "Next")
	{
		Director::getInstance()->getRunningScene()->addChild(layer);
	}
}

