#include "hero.h"
USING_NS_CC;

Hero::Hero()
{

}

Hero::~Hero()
{

}

bool Hero::init()
{
	if (!People::init())
		return false;

	towards = HeroTowards::right;
	isIdle = true;
	lastTowards = towards;
	lastisIdle = isIdle;

	this->scheduleUpdate();
	auto KeyListener = EventListenerKeyboard::create();
	KeyListener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, Event* event) {
		keys[keycode] = true;
	};
	KeyListener->onKeyReleased = [=](EventKeyboard::KeyCode keycode, Event* event) {
		keys[keycode] = false;
	};

	// 使用EventDispatcher来处理各种各样的事件，如触摸和其他键盘事件。

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(KeyListener, this);
	
	return true;
}




Hero* Hero::create(const char* file)
{
	Hero* sprite = new Hero();
	if (sprite && sprite->initWithFile(file))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);

	return nullptr;
}


//void Hero::attack(Vec2 target)
//{	
//	if (projectileNum > 0)
//	{
//		Projectile = Sprite::create("projectile.png");
//		this->addChild(Projectile);
//		auto begin = this->getPosition();
//		auto route = target - begin;
//		route.normalize();
//		route *= 1000;
//		auto move = MoveTo::create(1.f, route);
//		Projectile->runAction(move);
//
//		//每一次攻击都会使子弹数量减少
//		projectileNum--;
//	}
//}
//
//void Hero::getHurt(Hero& enemy)
//{
//	_HP -= enemy._ATK;
//}
//
void Hero::fillBullet()
{
	static int cnt = 2;
	cnt++;
	//log("in fillBullet");
	if (cnt % 160 == 1 && bulletNum < MAX_BULLET_NUM)
	{
		log("fill Bullet");
		bulletNum++;
	}
	if (cnt == 1000000)
		cnt = 0;
}
void Hero::fillEnergy()
{
	energy++;
}
//
//void Hero::fillEnergy()
//{
//	if (energy < 6)
//		energy++;
//}
//
//void Hero::specialAttack(Vec2 target)
//{
	//if (energy == MAX_ENERGY)
	//{
	//	Blast = Sprite::create("blast.png");
	//	this->addChild(Blast);
	//	Blast->setRotation(180);
	//	Blast->setScale(0.2);
	//	auto begin = this->getPosition();
	//	auto route = target - begin;
	//	route.normalize();
	//	auto Angle = route.angle(Vec2(1, 0),route);     //得到发射方向与冲击波初始方向夹角
	//	Angle = Angle / 3.14159 * 180;           //转换成角度
	//	Blast->setRotation(Angle);
	//	route *= 1000;
	//	auto move = MoveTo::create(1.f, route);
	//	Blast->runAction(move);
	//	log("successfully shoot");
	//	if ((int)Blast->getPosition().getLength()==1000)
	//		removeChild(Blast);

	//	energy = 0;        //能量清空 
	//}
//}


//void Hero::levelUp()
//{
//	_ATK += LEVEL_UP_ATK;
//	_HP += LEVEL_UP_HP;
//}

void Hero::bindBullet(const char* bulletType)
{
	BulletType = bulletType;
}

void Hero::getDiamond()
{
	diamondNum++;
	_HP += AmplificationRate * InitHP;
	_ATK += AmplificationRate * InitATK;
	//一个闪动特效，说明他升级了
	auto recov = TintTo::create(0.2f, this->getColor());
	auto tintto = TintTo::create(0.2f, Color3B::WHITE);
	auto seq = Sequence::create(tintto, recov, nullptr);
	runAction(Sequence::create(seq, seq->clone(), seq->clone(), nullptr));
	log("hero shine");
}

void Hero::update(float dlt)
{
	Node::update(dlt);
	auto w = EventKeyboard::KeyCode::KEY_W, a = EventKeyboard::KeyCode::KEY_A;
	auto s = EventKeyboard::KeyCode::KEY_S, d = EventKeyboard::KeyCode::KEY_D;
	if (isKeyPressed(w) || isKeyPressed(s) || isKeyPressed(a) || isKeyPressed(d))
	{
		isIdle = false;
		if (isKeyPressed(w))
		{
			towards = HeroTowards::front;
			keyPressedDuration(w);
		}
		else if (isKeyPressed(s))
		{
			towards = HeroTowards::back;
			keyPressedDuration(s);
		}
		else if (isKeyPressed(a))
		{
			towards = HeroTowards::left;
			keyPressedDuration(a);
		}
		else if (isKeyPressed(d))
		{
			towards = HeroTowards::right;
			keyPressedDuration(d);
		}
	}
	else
		isIdle = true;
	moveAnimation();

	fillBullet();

}

bool Hero::isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	return keys[keyCode];
}

void Hero::keyPressedDuration(EventKeyboard::KeyCode keycode)
{

	int offsetx = 0, offsety = 0;
	switch (keycode)
	{
		case EventKeyboard::KeyCode::KEY_W:
			offsety = 3;
			break;
		case EventKeyboard::KeyCode::KEY_S:
			offsety = -3;
			break;
		case EventKeyboard::KeyCode::KEY_A:
			offsetx = -3;
			break;
		case EventKeyboard::KeyCode::KEY_D:
			offsetx = 3;
			break;
		default:
			offsetx = offsety = 0;
			break;
	}

	//判断是否与障碍物相撞
	auto position = this->getPosition();
	auto aimx = this->getContentSize().width / 2;
	auto aimy = this->getContentSize().height / 2;


	if (offsetx == 0)
		aimx = 0;
	if (offsetx < 0)
		aimx = -aimx;
	if (offsety == 0)
		aimy = 0;
	if (offsety < 0)
		aimy = -aimy;
	position = Vec2toTile(position + Vec2(aimx, aimy));
		auto wallgrp = _map->getLayer("barrier");
	int tilegid = wallgrp->getTileGIDAt(position);
	log("tilegid:%d", tilegid);

	if (tilegid)
		return;

	auto moveTo = MoveTo::create(0.01, Vec2(this->getPositionX() + offsetx, this->getPositionY() + offsety));
	this->runAction(moveTo);
}

Vec2 Hero::Vec2toTile(Vec2 position)
{
	int x = position.x / _map->getTileSize().width;
	int y = ((_map->getMapSize().height * _map->getTileSize().height) - position.y) / _map->getTileSize().height;
	return Vec2(x, y);
}

void Hero::bindMap(TMXTiledMap* map)
{
	_map = map;
}

void Hero::moveAnimation()
{
	static bool isFirst = true;
	if (isFirst)
	{
		now = m_idle_right;
		runAction(now);
	}
	if (isStatusChanged())
	{
		if (!isFirst)
			stopAction(now);
		switch (towards)
		{
			case HeroTowards::front:
				lastTowards = HeroTowards::front;
				lastisIdle = isIdle;
				now = isIdle ? m_idle_front : m_front;
				break;
			case HeroTowards::back:
				lastTowards = HeroTowards::back;
				lastisIdle = isIdle;
				now = isIdle ? m_idle_back : m_back;
				break;
			case HeroTowards::left:
				lastTowards = HeroTowards::left;
				lastisIdle = isIdle;
				now = isIdle ? m_idle_left : m_left;
				break;
			case HeroTowards::right:
				lastTowards = HeroTowards::right;
				lastisIdle = isIdle;
				now = isIdle ? m_idle_right : m_right;
				break;
			defalt:
				break;
		}
		now->autorelease();
		runAction(now);
		now->retain();
	}

	isFirst = false;
}

bool Hero::isStatusChanged()
{
	return !(lastisIdle == isIdle && lastTowards == towards);
}

int Hero::getDiamondNum()
{
	return diamondNum;
}







