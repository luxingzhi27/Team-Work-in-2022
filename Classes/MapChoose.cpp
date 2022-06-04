#include "MapChoose.h"
#include "FastCreating.h"
bool MapChoose::init()
{
	if (!Scene::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//Sprite* myHero[5];
	//for (int i = 0; i < 5; i++)
	//{
	//	char imageName[15] = { 0 };
	//	sprintf(imageName, "myHero%d", i);
	//	myHero[i] = Sprite::create(imageName);
	//	myHero[i]->setPosition(visibleSize.width * (i + 1) / 6, visibleSize.height / 2);
	//	this->addChild(myHero[i], i);
	//}
	//����һ����ʾ�ı�
	auto label = Label::createWithTTF("Choose Your Map", "fonts/Marker Felt.ttf", 58);
	label->setTextColor(Color4B::ORANGE);
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	label->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height);
	label->setScaleX(1.35f);
	label->enableShadow();
	this->addChild(label);

	//����һ����ѡ��
	for (int i = 0; i < MapNUM; i++)
	{
		MapBox[i] = CheckBox::create("US.png", "US.png", "S.png", "US.png", "S.png");
		addChild(MapBox[i]);
		MapBox[i]->setScale(0.7);
		MapBox[i]->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		MapBox[i]->setPosition(Vec2(visibleSize.width * (i + 1) / (MapNUM + 1), visibleSize.height / 3));
	}
	MapBox[MapNum]->setSelected(true);
	MapBox[0]->addEventListener([&](Ref* ref, ui::CheckBox::EventType type)
		{
			if (type == CheckBox::EventType::SELECTED)
			{
				for (int m = 0; m < MapNUM; m++)
				{
					if (MapBox[m]->isSelected() && m != 0)
						MapBox[m]->setSelected(false);
				}
				MapNum = 0;
			}
		});
	MapBox[1]->addEventListener([&](Ref* ref, ui::CheckBox::EventType type)
		{
			if (type == CheckBox::EventType::SELECTED)
			{
				for (int m = 0; m < MapNUM; m++)
				{
					if (MapBox[m]->isSelected() && m != 1)
						MapBox[m]->setSelected(false);
				}
				MapNum = 1;
			}
		});
	MapBox[2]->addEventListener([&](Ref* ref, ui::CheckBox::EventType type)
		{
			if (type == CheckBox::EventType::SELECTED)
			{
				for (int m = 0; m < MapNUM; m++)
				{
					if (MapBox[m]->isSelected() && m != 2)
						MapBox[m]->setSelected(false);
				}
				MapNum = 2;
			}
		});
	MapBox[3]->addEventListener([&](Ref* ref, ui::CheckBox::EventType type)
		{
			if (type == CheckBox::EventType::SELECTED)
			{
				for (int m = 0; m < MapNUM; m++)
				{
					if (MapBox[m]->isSelected() && m != 3)
						MapBox[m]->setSelected(false);
				}
				MapNum = 3;
			}
		});


	//����һ�����ذ�ť
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
	ReturnButton->setPosition(Vec2(origin.x + ReturnButton->getContentSize().width, origin.y + ReturnButton->getContentSize().height / 3));
	addChild(ReturnButton);

	//����һ��next��ť
	auto NextButton = Button_Create("Next", [](Ref* ref, Widget::TouchEventType type)
		{
			switch (type) {
			case Widget::TouchEventType::ENDED:
				Director::getInstance()->popScene();
				break;
			default:
				break;
			}
		});
	NextButton->setScale(0.7);
	NextButton->setPosition(Vec2(visibleSize.width / 1.5 + NextButton->getContentSize().width / 2, origin.y + NextButton->getContentSize().height / 3));
	addChild(NextButton);


	//����һ���˳���ť
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