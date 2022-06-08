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
	bindPhysicsBody();

	if (isai==false)
	{
		auto TouchListener = EventListenerTouchOneByOne::create();
		TouchListener->onTouchBegan = CC_CALLBACK_2(Shirley::onTouchBegan, this);
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(TouchListener, this);
	}
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

bool Shirley::bindPhysicsBody()
{

	auto physicsBody = cocos2d::PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.0f, 1.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	physicsBody->setContactTestBitmask(HERO_CONTACT_MASK);
	physicsBody->setCategoryBitmask(HERO_CATEGORY_MASK);
	physicsBody->setTag(HERO_TAG);
	this->setPhysicsBody(physicsBody);
	/*Director::getInstance()->getRunningScene()->getPhysics3DWorld()->setDebugDrawEnable(false);
	Director::getInstance()->getRunningScene()->setPhysics3DDebugCamera(nullptr);*/
	return true;

}

void Shirley::attack(Vec2 target)
{
	log("Attack");
	if (bulletNum > 1)
	{
		_bullet = Bullet::create(BulletType);
		_bullet->bindHero(static_cast<Hero*>(this));
		log("Bullet Created");
		_bullet->setAttributes(_ATK, _Reach, _Speed);
		auto begin = this->getPosition() + this->getParent()->getPosition();
		auto route = target - begin;
		route.normalize();

		route *= _Reach;
		auto Angle = route.angle(Vec2(1, 0), route);
		Angle = -Angle / 3.14159 * 180;
		_bullet->setRotation(route.y > 0 ? Angle : -Angle);

		_bullet->setPosition(this->getPosition() + route / _Reach * (this->getContentSize().width * 2));
		this->getParent()->addChild(_bullet);
		auto move = MoveBy::create(_Speed, route);

		auto selfRemove = RemoveSelf::create();
		_bullet->runAction(Sequence::create(move, selfRemove, nullptr));
		//每一次攻击都会使子弹数量减少
		bulletNum--;
		log("bulletNum:%d", bulletNum);
	}
}

bool Shirley::onTouchBegan(Touch* touch, Event* unused_event)
{
	if (isai == false)
	{
		auto TouchLocation = Vec2(touch->getLocation().x, touch->getLocation().y);
		//log("TOUCH");
		attack(TouchLocation);
		return true;
	}{}
}



void Shirley::specialAttack(Vec2 target)
{
}

