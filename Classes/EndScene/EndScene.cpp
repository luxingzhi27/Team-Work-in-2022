#include "EndScene/EndScene.h"

cocos2d::Scene* EndScene::createScene(bool isVictory)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto scene = EndScene::create();
	//创建一个标签 显示胜利或者失败
	auto label = Label::createWithTTF("", "fonts/Marker Felt.ttf", 70);
	label->setTextColor(Color4B::ORANGE);
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	label->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height/2 - label->getContentSize().height);
	label->setScaleX(1.35f);
	label->enableShadow();
	if (isVictory) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("win.mp3");
		label->setString("VICTORY!");
	}
	else {
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("lost.mp3");
		label->setString("DEFEAT!");
	}
	scene->addChild(label);
	return scene;
}

bool EndScene::init()
{
	if (!Scene::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto menuImage1 = MenuImageCreate();
	menuImage1->setCallback(CC_CALLBACK_1(EndScene::menuItemCallback,
		this,
		"Main Menu"));
	auto pMenu1 = MenuCreate("Main Menu", menuImage1,
		Vec2(visibleSize.width / 2, visibleSize.height / 3));
	addChild(pMenu1);
	//退出按钮
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

}

void EndScene::menuItemCallback(cocos2d::Ref* pSender, std::string eventname)
{
	if (eventname == "Main Menu")
		Director::getInstance()->replaceScene(StartScene::create());
}
