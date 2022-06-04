#include "StartScene.h" 
#include "SettingScene.h" 
#include "FastCreating.h"
#include "HeroChoose.h"
bool StartScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	//设置背景图片
	auto bgImage = Sprite::create("bg.webp");
	bgImage->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	bgImage->setPosition(Vec2(origin.x, origin.y));
	//缩放图片使之铺满全屏
	auto ContentSize = bgImage->getContentSize();
	bgImage->setScale(visibleSize.width / ContentSize.width, visibleSize.height / ContentSize.height);
	this->addChild(bgImage);

	//添加游戏标题
	auto label = Label::createWithTTF("Wild fighting", "fonts/Marker Felt.ttf", 58);
	label->setTextColor(Color4B::ORANGE);
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	label->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height-label->getContentSize().height );
	label->setScaleX(1.35f);
	label->enableShadow();
	this->addChild(label);

	//按钮创建
	auto StartButton = Button_Create("Start", [](Ref* ref, Widget::TouchEventType type)
		{
			switch (type) {
			case Widget::TouchEventType::ENDED:
				Director::getInstance()->pushScene(HeroChoose::create());
				break;
			default:
				break;
			}
		});
	auto SettingsButton = Button_Create("Settings", [](Ref* ref, Widget::TouchEventType type)
		{
			switch (type) {
			case Widget::TouchEventType::ENDED:
				Director::getInstance()->pushScene(SettingScene::createScene());
				break;
			default:
				break;
			}
		});
	auto HelpButton = Button_Create("Help", [](Ref* ref, Widget::TouchEventType type)
		{
			switch (type) {
			case Widget::TouchEventType::ENDED:
				//Director::getInstance()->pushScene(SettingScene::createScene());
				break;
			default:
				break;
			}
		});
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
	Button_Add({ StartButton,SettingsButton,HelpButton});//将按钮添加到屏幕上
	//CCLayerMultiplex{ CCLyaer1,CCLayer2...Null };
	//((CCLayerMultiplex*)m_pParent)->switchTo(0);
	//CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("bg2.png");
	//bg->setTexture(texture);
	return true;
}


void StartScene::Button_Add(std::vector<Button*> buttonList) 
{
	for (auto iterator = buttonList.begin(); iterator < buttonList.end(); iterator++)
	{
		(*iterator)->setPosition(Vec2(
			origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height * 0.6f - (iterator - buttonList.begin())*0.85f * (*iterator)->getContentSize().height));
		this->addChild(*iterator);
	}

}

StartScene::StartScene()//构造函数中获取窗口相关参数 
{
	//在构造函数中进行窗口变量获取和音乐播放
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music.mp3", true);
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
}
