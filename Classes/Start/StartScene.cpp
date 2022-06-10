#include "StartScene.h" 

bool StartScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	//���ñ���ͼƬ
	auto bgImage = Sprite::create("preview0.jpg");
	bgImage->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	bgImage->setPosition(Vec2(origin.x, origin.y));
	//����ͼƬʹ֮����ȫ��
	auto ContentSize = bgImage->getContentSize();
	bgImage->setScale(visibleSize.width / ContentSize.width, visibleSize.height / ContentSize.height);
	this->addChild(bgImage);

	//�����Ϸ����
	auto label = Label::createWithTTF("Wild fighting", "fonts/Marker Felt.ttf", 58);
	label->setTextColor(Color4B::ORANGE);
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	label->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height-label->getContentSize().height );
	label->setScaleX(1.35f);
	label->enableShadow();
	this->addChild(label);

	//��ť����
	auto StartButton = Button_Create("Start", [](Ref* ref, Widget::TouchEventType type)
		{
			switch (type) {
			case Widget::TouchEventType::ENDED:
				Director::getInstance()->getRunningScene()->addChild(HeroChoose::create());
				break;
			default:
				break;
			}
		});
	auto SettingsButton = Button_Create("Settings", [](Ref* ref, Widget::TouchEventType type)
		{
			switch (type) {
			case Widget::TouchEventType::ENDED:
				Director::getInstance()->replaceScene(SettingScene::createScene());
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
	Button_Add({ StartButton,SettingsButton,HelpButton});//����ť��ӵ���Ļ��

	return true;
}


void StartScene::Button_Add(std::vector<Button*> buttonList) 
{
	for (auto iterator = buttonList.begin(); iterator < buttonList.end(); iterator++)
	{
		(*iterator)->setPosition(Vec2(
			origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height * 0.6f - (iterator - buttonList.begin())*0.7f * (*iterator)->getContentSize().height));
		this->addChild(*iterator);
	}

}

StartScene::StartScene()//���캯���л�ȡ������ز��� 
{
	//�ڹ��캯���н��д��ڱ�����ȡ�����ֲ���
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

}
