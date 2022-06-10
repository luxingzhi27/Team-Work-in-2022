#include "AIChoose.h"
#include "SettingandCreating/FastCreating.h"
#include"Map/mymap.h"
bool AIChoose::init()
{
	if (!Layer::init())
		return false;
	auto VisibleSize = Director::getInstance()->getVisibleSize();
	auto bg = LayerColor::create(Color4B::GRAY);
	addChild(bg);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("Choose The Number of AI Players", "fonts/Marker Felt.ttf", 58);
	label->setTextColor(Color4B::ORANGE);
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	label->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height);
	label->setScaleX(1.35f);
	label->enableShadow();
	this->addChild(label);

	label2 = Label::createWithSystemFont("", "fonts/Marker Felt.ttf", 58);
	label2->setTextColor(Color4B::ORANGE);
	label2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	label2->setScaleX(1.35f);
	label2->enableShadow();
	this->addChild(label2);
	NumOfAI = 1;
	auto path = StringUtils::format("%d/%d", NumOfAI, MAX_AI_NUM);
	label2->setString(path);
	auto slider = Slider::create();
	slider->loadBarTexture("Slider_Back.png"); // what the slider looks like
	slider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
	slider->loadProgressBarTexture("Slider_PressBar.png");
	slider->setScale(1.2, 1.4);
	slider->setPercent(NumOfAI * 100 / MAX_AI_NUM );
	slider->addEventListener([&](Ref* sender, Slider::EventType type) {
		if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
			int percent = dynamic_cast<Slider*>(sender)->getPercent();
			NumOfAI = percent * MAX_AI_NUM / 100;
			auto path = StringUtils::format("%d/%d", NumOfAI, MAX_AI_NUM);
			label2->setString(path);
		}
		});
	slider->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	label2->setPosition(Vec2(slider->getPosition()) + Vec2(0, 50));
	this->addChild(slider);

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

	auto menuImage1 = MenuImageCreate();
	menuImage1->setCallback(CC_CALLBACK_1(AIChoose::menuItemCallback,
		this,
		"Main Menu"));
	auto pMenu1 = MenuCreate("Main Menu", menuImage1,
		Vec2(visibleSize.width/2, visibleSize.height/3));
	addChild(pMenu1);

	auto menuImage2 = MenuImageCreate();
	menuImage2->setCallback(CC_CALLBACK_1(AIChoose::menuItemCallback,
		this,
		"Return"));
	auto pMenu2 = MenuCreate("Return", menuImage2,
		Vec2(visibleSize.width / 4, visibleSize.height / 7));
	addChild(pMenu2);

	auto menuImage3 = MenuImageCreate();
	menuImage3->setCallback(CC_CALLBACK_1(AIChoose::menuItemCallback,
		this,
		"Next"));
	auto pMenu3 = MenuCreate("Next", menuImage3,
		Vec2(visibleSize.width * 3 / 4, visibleSize.height / 7));
	addChild(pMenu3);


	return true;
}

void AIChoose::menuItemCallback(cocos2d::Ref* pSender, std::string eventname)
{
	this->removeFromParentAndCleanup(true);
	if (eventname == "Main Menu")
		Director::getInstance()->replaceScene(StartScene::create());
	if (eventname == "Return")
		Director::getInstance()->getRunningScene()->addChild(HeroChoose::create());
	if (eventname == "Next")
		Director::getInstance()->replaceScene(MapLayer::createMapScene());
}

