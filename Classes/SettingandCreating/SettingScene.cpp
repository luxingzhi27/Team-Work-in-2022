#include "SettingScene.h" 

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
				Director::getInstance()->replaceScene(StartScene::create());
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

	//ÍË³ö°´Å¥
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
