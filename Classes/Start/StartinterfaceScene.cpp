#include "StartinterfaceScene.h"

USING_NS_CC;


bool Startinterface::init()
{
	if (!Scene::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��ʼ����ı���ͼƬ
	auto sprite = Sprite::create("preview2.png");
	sprite->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	sprite->setTextureRect(Rect(0, 0, sprite->getContentSize().width, sprite->getContentSize().height));
	this->addChild(sprite, 0);




	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("start.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1);
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(Startinterface::PlayMusic), 4.0f);
	

	//�ص�����������
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(Startinterface::AlterToStartScene), 3.0f);//�ӳ��л�����
	return true;
}

void Startinterface::PlayMusic(float f1)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("combat_music.mp3", true);
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
}


void Startinterface::AlterToStartScene(float fl)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, StartScene::create()));
}

