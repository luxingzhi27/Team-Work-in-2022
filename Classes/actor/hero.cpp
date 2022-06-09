#include "hero.h"
USING_NS_CC;
#include<vector>
#include<cmath>
#include<cstdlib>
#include<ctime>
using namespace std;

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
	this->schedule(CC_SCHEDULE_SELECTOR(Hero::fillBullet), 1.f);
	this->schedule(CC_SCHEDULE_SELECTOR(Hero::fillHP), 1.f);
	if (isai == false)           //如果不是ai才执行这一步
	{
		auto KeyListener = EventListenerKeyboard::create();
		KeyListener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, Event* event) {
			keys[keycode] = true;
		};
		KeyListener->onKeyReleased = [=](EventKeyboard::KeyCode keycode, Event* event) {
			keys[keycode] = false;
		};
		// 使用EventDispatcher来处理各种各样的事件，如触摸和其他键盘事件。
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(KeyListener, this);
	}
	
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
void Hero::fillBullet(float dt)
{
	if (bulletNum < MAX_BULLET_NUM)
	{
		log("fill Bullet");
		bulletNum++;
	}
}
void Hero::fillHP(float dt)
{
	if (_HP < SHIRLEY_HP)
	{
		_HP += 300;
		if (_HP > SHIRLEY_HP)
			_HP = SHIRLEY_HP;
	}
}
void Hero::fillEnergy()
{
	if(energy< SHIRLEY_MAX_ENERGY)
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
	if (isai == false) 
	{
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
	}
	else
	{
		aiMove();
	}
	moveAnimation();
	grassInvisible();
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
	if (isFirst)
	{
		now = m_idle_right;
		runAction(now);
		isFirst = false;
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

void Hero::grassInvisible()
{
	auto grassLayer = _map->getLayer("grass");
	auto pos = Vec2toTile(getPosition());
	int gid = grassLayer->getTileGIDAt(pos);
	if (gid)
	{
		if (isai == false)
			setOpacity(128);
		else
			setOpacity(1);
	}
	else
		setOpacity(255);
}

Vec2 Hero::aiSearch(int &aimtype)
{
	auto children=getParent()->getChildren();
	vector<Node*> treasure;
	vector<Node*> hero;
	vector<Node*> diamond;

	auto aipos = getPosition();
	for (auto i : children)
	{
		if (i != this)
		{
			auto pos = i->getPosition();
			auto distance = pow(aipos.x - pos.x, 2) + pow(aipos.y - pos.y, 2);
			if (distance < 10000)
			{
				if (i->getTag() == TREASURE_TAG)
					treasure.push_back(i);
				if (i->getTag() == HERO_TAG)
					hero.push_back(i);
				if (i->getTag() == DIAMOND_TAG)
					diamond.push_back(i);
			}
		}
	}
	if (!hero.empty())
	{
		log("hero!");
		aimtype = HERO_TAG;
		return hero[0]->getPosition();
	}
	else if (!diamond.empty())
	{
		log("diamond!");
		aimtype = DIAMOND_TAG;
		return diamond[0]->getPosition();
	}
	else if (!treasure.empty())
	{
		log("treasure!");
		aimtype = TREASURE_TAG;
		return treasure[0]->getPosition();
	}
	else
	{
		log("null");
		return Vec2(5000, 5000);
	}
}

void Hero::aiMove()
{
	int aimtype=-1;
	int offsetx = 0, offsety = 0;
	int choose=0;
	auto aim = aiSearch(aimtype);
	auto pos = getPosition();
	if ( aim!= Vec2(5000,5000))
	{
		int offset=60;
		if (aimtype == DIAMOND_TAG)
			offset = -3;
		else
			attack(aim);
		if (aim.x+offset < pos.x)
			choose = 3;
		else if (aim.y+offset < pos.y)
			choose = 2;
		else if (aim.x-offset > pos.x)
			choose = 4;
		else if (aim.y+offset > pos.y)
			choose = 1;
	}
	else
	{
		srand((unsigned)time(0));
		choose = rand() % 5;
	}
	if (choose == 0)
		isIdle = true;
	else
	{
		isIdle = false;
		if (choose == 1)
		{
			towards = HeroTowards::front;
			offsetx = 0, offsety = 3;
		}
		else if (choose == 2)
		{
			towards = HeroTowards::back;
			offsetx = 0, offsety = -3;
		}
		else if (choose == 3)
		{
			towards = HeroTowards::left;
			offsetx = -3, offsety = 0;
		}
		else
		{
			towards = HeroTowards::right;
			offsetx = 3, offsety = 0;
		}
	}

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

	if (tilegid)
		return;

	auto move = MoveTo::create(0.01f, getPosition()+Vec2(offsetx,offsety));
	runAction(move);
}


void Hero::attack(Vec2 target)
{
}


void Hero::setai()
{
	isai = true;
}










