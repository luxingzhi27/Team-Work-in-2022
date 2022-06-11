#include "HelpLayer/HelpLayer.h"

cocos2d::Layer* HelpLayer::createLayer(std::string Choose)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto layer = HelpLayer::create();

	//�������β�
	LayerColor* bg = LayerColor::create(Color4B::GRAY);
	layer->addChild(bg);

	//����һ����ǩ ��ʾʤ������ʧ�� �����ϲ��м�
	auto label = Label::createWithTTF("", "fonts/Marker Felt.ttf", 70);
	label->setTextColor(Color4B::ORANGE);
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	label->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height  - label->getContentSize().height-70);
	label->setScaleX(1.35f);
	label->enableShadow();
	label->setString(Choose);  //��ǩ����
	layer->addChild(label);

	//�˳���ť
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
	layer->addChild(ExitImage);

	if (Choose == "How To Play")
	{
		//���ܰ���
		
		auto pMenu1 = LabelCreate("UP:         W            LEFT:        A");
		pMenu1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - pMenu1->getContentSize().height * 3.5-30));
		layer->addChild(pMenu1);

		auto pMenu2 = LabelCreate("DOWN:     S            RIGHT:      D");
		pMenu2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - pMenu2->getContentSize().height * 4.5-60));
		layer->addChild(pMenu2);

		//���ܹ�����ʽ
		auto pMenu3 = LabelCreate("BULLET:  The Left Mouse Button");
		pMenu3->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - pMenu3->getContentSize().height * 5.5-90));
		layer->addChild(pMenu3);

		auto pMenu4 = LabelCreate("ATACK:  The Right Mouse Button");
		pMenu4->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - pMenu4->getContentSize().height * 6.5-120));
		layer->addChild(pMenu4);

		//���ܱ���
		auto Truesure = Sprite::create("treasure.png");
		Truesure->setPosition(Vec2(pMenu4->getPosition()) - Vec2(300, Truesure->getContentSize().height) - Vec2(0, 30));
		layer->addChild(Truesure);
		auto pMenu5 = LabelCreate("Break it to get diamond");
		pMenu5->setPosition(Vec2(Truesure->getPosition())+Vec2(pMenu5->getContentSize().width,0) );
		layer->addChild(pMenu5);

		//������ʯ
		auto diamond = Sprite::create("diamond.png");
		diamond->setPosition(Vec2(pMenu4->getPosition()) - Vec2(300, diamond->getContentSize().height*3) - Vec2(0, 60));
		layer->addChild(diamond);
		auto pMenu6 = LabelCreate("Get it to increase ATK");
		pMenu6->setPosition(Vec2(diamond->getPosition()) + Vec2(pMenu5->getContentSize().width, 0));
		layer->addChild(pMenu6);

	}
	else if(Choose == "Developers")
	{
		auto pMenu1 = LabelCreate("luxingzhi27");
		pMenu1->setColor(Color3B::BLACK);
		pMenu1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - pMenu1->getContentSize().height * 3.5));
		layer->addChild(pMenu1);

		auto pMenu2 = LabelCreate("jingziccc");
		pMenu2->setColor(Color3B::BLACK);
		pMenu2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - pMenu2->getContentSize().height * 5.5));
		layer->addChild(pMenu2);

		auto pMenu3 = LabelCreate("childe-Liu");
		pMenu3->setColor(Color3B::BLACK);
		pMenu3->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - pMenu3->getContentSize().height * 7.5));
		layer->addChild(pMenu3);

		auto pMenu4 = LabelCreate("ALL FROM TJ UNIVERSITY");
		pMenu4->setColor(Color3B::BLACK);
		pMenu4->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - pMenu4->getContentSize().height * 9.5));
		layer->addChild(pMenu4);
	}
	//���ذ�ť
	auto menuImage1 = MenuImageCreate();
	menuImage1->setCallback(CC_CALLBACK_1(HelpLayer::menuItemCallback2,
		layer,
		"Return"));
	auto pMenu = MenuCreate("Return", menuImage1,
		Vec2(100, 50));

	layer->addChild(pMenu);

	return layer;
}

bool HelpLayer::init()
{
	if (!Layer::init())
		return false;
	//�������β�
	LayerColor* bg = LayerColor::create(Color4B::GRAY);
	addChild(bg);

	//�˳���ť
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

	//����������   �����·�
	auto menuImage1 = MenuImageCreate();
	menuImage1->setCallback(CC_CALLBACK_1(HelpLayer::menuItemCallback,
		this,
		"Main Menu"));
	auto pMenu1 = MenuCreate("Main Menu", menuImage1,
		Vec2(visibleSize.width / 2, menuImage1->getContentSize().height-40));
	addChild(pMenu1);

	//HOW TO PLAY   �����Ϸ�
	auto menuImage2 = MenuImageCreate();
	menuImage2->setCallback(CC_CALLBACK_1(HelpLayer::menuItemCallback,
		this,
		"How To Play"));
	auto pMenu2 = MenuCreate("How To Play", menuImage2,
		Vec2(visibleSize.width / 2, visibleSize.height - menuImage2->getContentSize().height));
	addChild(pMenu2);

	//������  �����м�
	auto menuImage3 = MenuImageCreate();
	menuImage3->setCallback(CC_CALLBACK_1(HelpLayer::menuItemCallback,
		this,
		"Developers"));
	auto pMenu3 = MenuCreate("Developers", menuImage3,
		Vec2(visibleSize.width / 2, visibleSize.height - menuImage3->getContentSize().height * 2+20));
	addChild(pMenu3);

	return true;
}

void HelpLayer::menuItemCallback(cocos2d::Ref* pSender, std::string eventname)
{
	this->removeFromParentAndCleanup(true);
	if (eventname == "How To Play")
		Director::getInstance()->getRunningScene()->addChild(HelpLayer::createLayer("How To Play"));
	if (eventname == "Developers")
		Director::getInstance()->getRunningScene()->addChild(HelpLayer::createLayer("Developers"));
}

void HelpLayer::menuItemCallback2(cocos2d::Ref* pSender, std::string eventname)
{
	this->removeFromParentAndCleanup(true);
	if (eventname == "Return")
		Director::getInstance()->getRunningScene()->addChild(HelpLayer::create());
}


