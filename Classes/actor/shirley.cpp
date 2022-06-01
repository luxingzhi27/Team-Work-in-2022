#include"shirley.h"
USING_NS_CC;

#define SHIRLEY_HP 2000
#define SHIRLEY_ATK 200

Shirley::Shirley()
{
}

Shirley::~Shirley()
{
}

bool Shirley::init()
{
	if (!Hero::init())
		return false;
	//m_status = IDLE;    //��ʼ����Ϊ��ֹ״̬
	
	//this->scheduleUpdate();

	//����HP��ATK
	setHP(SHIRLEY_HP);
	setATK(SHIRLEY_ATK);
	//�����ĸ��������߶���
	m_front = People::getAnimate("front", "hero1", 4, -1);
	m_back = People::getAnimate("back", "hero1", 4, -1);
	m_left = People::getAnimate("left", "hero1", 4, -1);
	m_right = People::getAnimate("right", "hero1", 4, -1);

	//�����ĸ�����վ������
	m_idle_front = People::getAnimate("front", "hero1", 1, -1);
	m_idle_back = People::getAnimate("back", "hero1", 1, -1);
	m_idle_left = People::getAnimate("left", "hero1", 1, -1);
	m_idle_right = People::getAnimate("right", "hero1", 1, -1);
	return true;
}

Shirley* Shirley::create(const char* file)
{
	Shirley* sprite = new Shirley();
	if (sprite && sprite->initWithFile(file))
	{
		sprite->autorelease();
		sprite->setHP(SHIRLEY_HP);
		sprite->setATK(SHIRLEY_ATK);
		return sprite;
	}
	CC_SAFE_DELETE(sprite);

	return nullptr;
}

void Shirley::attack(cocos2d::Vec2 target)
{
}

void Shirley::getHurt(Hero& enemy)
{
}

void Shirley::specialAttack(Vec2 target)
{
}

