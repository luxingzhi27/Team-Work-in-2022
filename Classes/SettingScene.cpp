#include "SettingScene.h" 
#include"StartScene.h"
#include "FastCreating.h"
using namespace std;
Scene* SettingScene::createScene()
{
	return SettingScene::create();
}
bool SettingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


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


	auto slider = Slider::create();
	slider->loadBarTexture("Slider_Back.png"); // what the slider looks like
	slider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
	slider->loadProgressBarTexture("Slider_PressBar.png");
	static float VolumePercent = 50;
	slider->setPercent(VolumePercent);
	slider->setScale(1.2, 1.4);
	float percent;
	slider->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			VolumePercent = SimpleAudioEngine::getInstance()->getBackgroundMusicVolume() * 100;
			percent = float(dynamic_cast<Slider*>(sender)->getPercent()) / 100.0f;
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(percent);
			break;
		default:
			break;
		}
		});
	slider->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(slider);

	auto label = Label::createWithTTF("Music Volume", "fonts/Marker Felt.ttf", 30);
	label->setTextColor(Color4B::ORANGE);
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	label->setPosition(Vec2(slider->getPosition().x-label->getContentSize().width, slider->getPosition().y));
	label->setScaleX(1.35f);
	label->enableShadow();
	this->addChild(label);

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


	////开启音乐按钮
	//auto on = Sprite::create("on.jpg");//创建两个精灵
	//auto off = Sprite::create("off.jpg");
	//on->setScale(0.5f);
	//off->setScale(0.5f);
	//auto onSpriteItem = MenuItemSprite::create(on, on);//创建两个精灵菜单项
	//auto offSpriteItem = MenuItemSprite::create(off, off);
	////根据音乐播放情况创建开关菜单项
	//MenuItemToggle* toggleItem;
	//if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
	//	CCLOG("On init");
	//	toggleItem = MenuItemToggle::createWithCallback(
	//		[&](Ref* ref) {
	//			auto item = dynamic_cast<MenuItemToggle*>(ref);
	//			if (item) {
	//				if (item->getSelectedIndex() == 0) {
	//					CCLOG("Play sound");
	//					SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	//				}
	//				else if (item->getSelectedIndex() == 1) {
	//					CCLOG("Silence");
	//					SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	//				}
	//			}
	//		}, onSpriteItem, offSpriteItem, NULL);
	//}
	//else {
	//	toggleItem = MenuItemToggle::createWithCallback(
	//		[&](Ref* ref) {
	//			auto item = dynamic_cast<MenuItemToggle*>(ref);
	//			if (item) {
	//				if (item->getSelectedIndex() == 0) {
	//					CCLOG("Play sound");
	//					SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	//				}
	//				else if (item->getSelectedIndex() == 1) {
	//					CCLOG("Silence");
	//					SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	//				}
	//			}
	//		}, offSpriteItem, onSpriteItem, NULL);
	//}
	//toggleItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	//toggleItem->setPosition(Vec2(origin.x + visibleSize.width * 29 / 32, origin.y + visibleSize.height * 17 / 28));
	////创建一个菜单
	//	//开启音效按钮
	//auto on2 = Sprite::create("on.jpg");//创建两个精灵
	//auto off2 = Sprite::create("off.jpg");
	//on2->setScale(0.5f);
	//off2->setScale(0.5f);
	//auto onSpriteItem2 = MenuItemSprite::create(on2, on2);//创建两个精灵菜单项
	//auto offSpriteItem2 = MenuItemSprite::create(off2, off2);
	//auto toggleItem2 = MenuItemToggle::createWithCallback([&](Ref* ref) {}, onSpriteItem2, offSpriteItem2, NULL);//创建一个开关菜单项
	//toggleItem2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	//toggleItem2->setPosition(Vec2(origin.x + visibleSize.width * 29 / 32, origin.y + visibleSize.height * 11 / 28));
	//Menu* menu = Menu::create(toggleItem, toggleItem2, NULL);
	//menu->setPosition(Vec2::ZERO);
	//this->addChild(menu);

	return true;
}



void SettingScene::buttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->popScene();
		break;
	default:
		break;
	}

}
