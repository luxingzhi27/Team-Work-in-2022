#include"nita.h"
#include"Map/mymap.h"
USING_NS_CC;

Nita::Nita()
{
}

Nita::~Nita()
{
}

bool Nita::init()
{
	if (!Hero::init())
		return false;
	//m_status = IDLE;    //��ʼ����Ϊ��ֹ״̬

	//this->scheduleUpdate();

	//����HP��ATK
	setHP(NITA_HP);
	InitHP = NITA_HP;
	MaxCurrentHP = NITA_HP;
	setATK(NITA_ATK);
	InitATK = NITA_ATK;
	setReach(NITA_REACH);
	setSpeed(NORMAL_SPEED);
	Max_energy = NITA_MAX_ENERGY;
	setTag(HERO_TAG);
	//�����ĸ��������߶���
	m_front = People::getAnimate("front", "hero2", 4, -1);
	m_back = People::getAnimate("back", "hero2", 4, -1);
	m_left = People::getAnimate("left", "hero2", 4, -1);
	m_right = People::getAnimate("right", "hero2", 4, -1);

	//�����ĸ�����վ������
	m_idle_front = People::getAnimate("front", "hero2", 1, -1);
	m_idle_back = People::getAnimate("back", "hero2", 1, -1);
	m_idle_left = People::getAnimate("left", "hero2", 1, -1);
	m_idle_right = People::getAnimate("right", "hero2", 1, -1);

	bindBullet("bullet4.png");
	bindSpell("blask4.png");

	if (isai == false)
	{
		auto MouseListener = EventListenerMouse::create();
		MouseListener->onMouseDown = CC_CALLBACK_1(Nita::onMouseDown, this);
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(MouseListener, this);

	}
	return true;
}

Nita* Nita::create(const char* file)
{
	Nita* sprite = new Nita();
	if (sprite && sprite->initWithFile(file) && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);

	return nullptr;
}


void Nita::attack(Vec2 target)
{
	if (!isai)
		log("Attack");

	if (bulletNum > 1)
	{
		_bullet = Bullet::create(BulletType);
		_bullet->bindHero(static_cast<Hero*>(this));
	//	log("Bullet Created");
		_bullet->setAttributes(_ATK, _Reach, _Speed);

		auto begin = this->getPosition() + this->getParent()->getPosition();
		auto route = target - begin;
		route.normalize();
		route *= _bullet->getReach();
		auto Angle = route.angle(Vec2(1, 0), route);
		Angle = -Angle / 3.14159 * 180;
		_bullet->setRotation(route.y > 0 ? Angle : -Angle);
		_bullet->setPosition(this->getPosition());

		this->getParent()->addChild(_bullet);
		auto move = MoveBy::create(_bullet->getSpeed(), route);

		auto selfRemove = RemoveSelf::create();
		_bullet->runAction(Sequence::create(move, selfRemove, nullptr));
		//ÿһ�ι�������ʹ�ӵ���������
		bulletNum--;
//		log("bulletNum:%d", bulletNum);
		//�����ӵ�����
	}
}

void Nita::onMouseDown(Event* event)
{
	if (isai == false)
	{
		EventMouse* ev = (EventMouse*)event;
		auto touchLocation = Vec2(ev->getCursorX(), ev->getCursorY());
		switch (ev->getMouseButton())
		{
			case EventMouse::MouseButton::BUTTON_LEFT:
				attack(touchLocation);
				break;
			case EventMouse::MouseButton::BUTTON_RIGHT:
				specialAttack(touchLocation);
				break;
		}
	}
}




void Nita::specialAttack(Vec2 target)
{
	if (energy == Max_energy)
	{
		energy = 0;
		log("special attack");

		_spell = Bullet::create(SpellType);
		_spell->setTag(SPELL_TAG);
		_spell->setAnchorPoint(Vec2(0, 0.5));
		_spell->setAttributes(_ATK * NITA_SPELL_RATE, NITA_SPELL_REACH, NITA_SPELL_SPEED);
		_spell->bindHero(static_cast<Hero*>(this));
		auto begin = this->getPosition() + this->getParent()->getPosition();
		auto route = target - begin;
		route.normalize();
		route *= _spell->getReach();
		auto Angle = route.angle(Vec2(1, 0), route);
		Angle = -Angle / 3.14159 * 180;
		_spell->setRotation(route.y > 0 ? Angle : -Angle);

		_spell->setPosition(this->getPosition());
		this->getParent()->addChild(_spell);
		auto move = MoveBy::create(_spell->getSpeed(), route);

		auto selfRemove = RemoveSelf::create();
		_spell->runAction(Sequence::create(move, selfRemove, nullptr));
	}

}