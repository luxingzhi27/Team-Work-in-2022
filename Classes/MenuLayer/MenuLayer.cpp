#include"MenuLayer.h"

bool MenuLayer::init()
{
	if (!Layer::init())
		return false;
	//LayerColor* tw = LayerColor::create(Color4B::BLACK);
	//addChild(tw);
	auto menuImage = MenuImageCreate();
	auto pMenu = MenuCreate("Menu", menuImage,
		Vec2(visibleSize.width - 90, visibleSize.height - 45));
	addChild(pMenu);
	//Director::getInstance()->startAnimation();
	auto menuImage1 = MenuImageCreate();
	menuImage1->setCallback(CC_CALLBACK_1(MenuLayer::menuItemCallback,
		this,
		"Main Menu"));
	auto pMenu1 = MenuCreate("Main Menu", menuImage1,
		Vec2(visibleSize.width /2, visibleSize.height - menuImage1->getContentSize().height*0.5));
	addChild(pMenu1);

	auto menuImage2 = MenuImageCreate();
	menuImage2->setCallback(CC_CALLBACK_1(MenuLayer::menuItemCallback,
		this,
		"Back To Game"));
	auto pMenu2 = MenuCreate("Back To Game", menuImage2,
		Vec2(visibleSize.width / 2, visibleSize.height - menuImage2->getContentSize().height * 1));
	addChild(pMenu2);

	auto menuImage3 = MenuImageCreate();
	menuImage3->setCallback(CC_CALLBACK_1(MenuLayer::menuItemCallback,
		this,
		"ChooseAgain"));
	auto pMenu3 = MenuCreate("ChooseAgain", menuImage3,
		Vec2(visibleSize.width / 2, visibleSize.height - menuImage3->getContentSize().height * 1.5));
	addChild(pMenu3);



	auto slider = Slider::create();
	slider->loadBarTexture("Slider_Back.png"); // what the slider looks like
	slider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
	slider->loadProgressBarTexture("Slider_PressBar.png");
	static float VolumePercent = SimpleAudioEngine::getInstance()->getBackgroundMusicVolume() * 100;
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
	label->setPosition(Vec2(slider->getPosition().x - label->getContentSize().width, slider->getPosition().y));
	label->setScaleX(1.35f);
	label->enableShadow();
	this->addChild(label);
}

void MenuLayer::AddMenu(std::vector<MenuItemFont*> menuList)
{

	for (auto iterator = menuList.begin(); iterator < menuList.end(); iterator++)
		(*iterator)->setPosition(Vec2(
			origin.x + visibleSize.width / 3,
			origin.y + visibleSize.height * 0.6f - (iterator - menuList.begin()) * 0.85f * (*iterator)->getContentSize().height));


}

void MenuLayer::menuItemCallback(cocos2d::Ref* pSender, std::string eventname)
{

	if (eventname == "Main Menu")
		Director::getInstance()->replaceScene(StartScene::create());
	if(eventname=="Back To Game")
		this->removeFromParentAndCleanup(true);
	if (eventname == "ChooseAgain")
		Director::getInstance()->replaceScene(HeroChoose::create());

}
