#include "StartinterfaceScene.h"

USING_NS_CC;


bool Startinterface::init()
{
	if (!Scene::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//开始界面的背景图片
	auto sprite = Sprite::create("OpeningImage.webp");
	if (sprite == nullptr)
	{
		return false;
	}
	else
	{
		sprite->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
		sprite->setTextureRect(Rect(0, 0, sprite->getContentSize().width, sprite->getContentSize().height));
		this->addChild(sprite, 0);
	}

	//回调函数的声明
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(Startinterface::AlterToStartScene), 4.0f);//延迟切换场景
	return true;
}


void Startinterface::AlterToStartScene(float fl)
{
	Director::getInstance()->replaceScene(TransitionFadeUp::create(1.0f, StartScene::create()));
}

