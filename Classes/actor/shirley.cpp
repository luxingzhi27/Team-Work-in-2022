#include"shirley.h"
#include"Map/mymap.h"
USING_NS_CC;

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
	//m_status = IDLE;    //初始人物为静止状态
	
	//this->scheduleUpdate();

	//加载HP和ATK
	setHP(SHIRLEY_HP);
	InitHP = SHIRLEY_HP;
	MaxCurrentHP = SHIRLEY_HP;
	setATK(SHIRLEY_ATK);
	InitATK = SHIRLEY_ATK;
	setReach(SHIRLEY_REACH);
	setSpeed(NORMAL_SPEED);
	Max_energy = SHIRLEY_MAX_ENERGY;
	setTag(HERO_TAG);
	//加载四个方向行走动画
	m_front = People::getAnimate("front", "hero1", 4, -1);
	m_back = People::getAnimate("back", "hero1", 4, -1);
	m_left = People::getAnimate("left", "hero1", 4, -1);
	m_right = People::getAnimate("right", "hero1", 4, -1);

	//加载四个方向站立动画
	m_idle_front = People::getAnimate("front", "hero1", 1, -1);
	m_idle_back = People::getAnimate("back", "hero1", 1, -1);
	m_idle_left = People::getAnimate("left", "hero1", 1, -1);
	m_idle_right = People::getAnimate("right", "hero1", 1, -1);

	bindBullet("bullet1.png");
	bindSpell("blask1.png");

	if (isai==false)
	{
		auto MouseListener = EventListenerMouse::create();
		if(isai==false)
			MouseListener->onMouseDown = CC_CALLBACK_1(Shirley::onMouseDown, this);
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(MouseListener, this);

	}
	return true;
}

Shirley* Shirley::create(const char* file)
{
	Shirley* sprite = new Shirley();
	if (sprite && sprite->initWithFile(file)&&sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);

	return nullptr;
}


void Shirley::attack(Vec2 target)
{
	if(!isai)
		log("Attack");

	if (bulletNum > 1)
	{
		_bullet = Bullet::create(BulletType);
		_bullet->bindHero(static_cast<Hero*>(this));
		//log("Bullet Created");
		_bullet->setAttributes(_ATK, _Reach, _Speed);

		auto begin = this->getPosition() + this->getParent()->getPosition();
		auto route = target - begin;
		route.normalize();
		route *= _bullet->getReach();
		auto Angle = route.angle(Vec2(1, 0), route);
		Angle = -Angle / 3.14159 * 180;
		_bullet->setRotation(route.y > 0 ? Angle : -Angle);
		_bullet->setPosition(this->getPosition() );

		this->getParent()->addChild(_bullet);
		auto move = MoveBy::create(_bullet->getSpeed(), route);

		auto selfRemove = RemoveSelf::create();
		_bullet->runAction(Sequence::create(move, selfRemove, nullptr));
		//每一次攻击都会使子弹数量减少
		bulletNum--;
		//log("bulletNum:%d", bulletNum);
		//更改子弹数量
	}
}

void Shirley::onMouseDown(Event* event)
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




void Shirley::specialAttack(Vec2 target)
{
	if (energy == Max_energy)
	{
		energy = 0;
		log("special attack");

		_spell = Bullet::create(SpellType, SPELL_TAG);
		_spell->setAnchorPoint(Vec2(0, 0.5));
		_spell->setAttributes(_ATK*SHIRLEY_SPELL_RATE, SHIRLEY_SPELL_REACH, SHIRLEY_SPELL_SPEED);
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

