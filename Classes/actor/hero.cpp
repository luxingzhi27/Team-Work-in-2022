#include "hero.h"
#include"Map/mymap.h"
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
	ProgressTimer* progressBlood=ProgressCreate(BloodTag, "BloodBar.png", Vec2(15, 75));
	this->addChild(progressBlood);
	this->schedule(CC_SCHEDULE_SELECTOR(Hero::BarUpdate));
	ProgressTimer* progressBlue = ProgressCreate(BlueTag, "BlueBar.png", Vec2(15, 65));
	this->addChild(progressBlue);

	bindPhysicsBody();

	towards = HeroTowards::right;
	isIdle = true;
	lastTowards = towards;
	lastisIdle = isIdle;

	this->scheduleUpdate();
	this->schedule(CC_SCHEDULE_SELECTOR(Hero::fillBullet), 1.0f);


	this->schedule(CC_SCHEDULE_SELECTOR(Hero::fillHP), 1.0f);
	this->schedule(CC_SCHEDULE_SELECTOR(Hero::outofFighting), 1.0f);
	this->schedule(SEL_SCHEDULE(&Hero::getPoisoning), 1.0f);

	if (isai == false)           //如果不是ai才执行这一步
	{
		ProgressTimer* progressBlue = ProgressCreate(BlueTag, "BlueBar.png", Vec2(15, 65));
		this->addChild(progressBlue);
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

bool Hero::bindPhysicsBody()
{
	auto _physicsBody = cocos2d::PhysicsBody::createCircle(30, PhysicsMaterial(0.0f, 1.0f, 0.0f));//(Size(20, 60), PhysicsMaterial(0.0f, 1.0f, 0.0f));
	_physicsBody->setDynamic(false);
	_physicsBody->setGravityEnable(false);
	_physicsBody->setRotationEnable(false);
	_physicsBody->setContactTestBitmask(HERO_CONTACT_MASK);
	_physicsBody->setCategoryBitmask(HERO_CATEGORY_MASK);
	_physicsBody->setTag(HERO_TAG);
	this->setPhysicsBody(_physicsBody);

	return true;

}


void Hero::BarUpdate(float dt)
{
	auto progressBlood = (ProgressTimer*)this->getChildByTag(BloodTag);
	progressBlood->setPercentage(double(_HP) / MaxCurrentHP * 100);  //这里是百分制显示
	auto progressBlue = (ProgressTimer*)this->getChildByTag(BlueTag);
	progressBlue->setPercentage(double(energy) / Max_energy * 100);  //这里是百分制显示

}

void Hero::fillBullet(float dt)
{

	if (bulletNum < MAX_BULLET_NUM)
	{
		if(!isai)
			log("fill Bullet");
		bulletNum++;
		//更改子弹数量
	}
}
void Hero::fillHP(float dt)
{
	if (_isfighting&&!this->isAI())
		log("be in fighting, %d",_isfighting);

	if (!_isfighting&&_HP < MaxCurrentHP)
	{
			
		_HP += 300;
		if (!this->isAI())
		{
			log("fill hp\ncurrent hp:%d", _HP);
		}
		if (_HP > MaxCurrentHP)
			_HP = MaxCurrentHP;
		//更改血条
	}
}
void Hero::fillEnergy()
{
	if (this!=nullptr&&_isAlive)
	{
		if (energy < Max_energy)
			energy++;
		_isfighting = 5;     //解除脱战
		//蓝条更改
	}
}

void Hero::bindBullet(const char* bulletType)
{
	BulletType = bulletType;
}

void Hero::bindSpell(const char* spelltype)
{
	SpellType = spelltype;
}

void Hero::getDiamond()
{
	diamondNum++;
	MaxCurrentHP+= static_cast<int>(AmplificationRate * InitHP);
	_HP += static_cast<int>(AmplificationRate * InitHP);
	_ATK += static_cast<int>( AmplificationRate * InitATK);
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

	if (!_isAlive)
	{
		die();
	}
		
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
	auto progressBlood = (ProgressTimer*)this->getChildByTag(BloodTag);
	auto progressBlue = (ProgressTimer*)this->getChildByTag(BlueTag);
	if (gid)
	{
		if (isai == false)
		{
			progressBlood->setOpacity(128);
			progressBlue->setOpacity(128);
			setOpacity(128);
		}
		else
		{
			progressBlood->setOpacity(1);
			progressBlue->setOpacity(1);
			setOpacity(1);
		}
	}
	else
	{
		progressBlood->setOpacity(255);
		progressBlue->setOpacity(255);
		setOpacity(255);
	}
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
			if (distance < 40000)
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
	//	log("hero!");
		aimtype = HERO_TAG;
		return hero[0]->getPosition();
	}
	else if (!diamond.empty())
	{
	//	log("diamond!");
		aimtype = DIAMOND_TAG;
		return diamond[0]->getPosition();
	}
	else if (!treasure.empty())
	{
	//	log("treasure!");
		aimtype = TREASURE_TAG;
		return treasure[0]->getPosition() ;
	}
	else
	{
	//	log("null");
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
		if(aimtype != DIAMOND_TAG)
		{
			specialAttack(aim+getParent()->getPosition()+Vec2(random(-5,5), random(-5, 5)));
			attack(aim + getParent()->getPosition() +Vec2(-1.5,-1.5)+Vec2(random(-5, 5), random(-5, 5)));
		}

		if ((aimtype == DIAMOND_TAG && pow(pos.x - aim.x, 2) + pow(pos.y - aim.y, 2) < 9) || (aimtype != DIAMOND_TAG && pow(pos.x - aim.x, 2) + pow(pos.y - aim.y, 2) < 8000))
			choose = 0;
		else
		{
			if (!((pos.x-aim.x)<4))
				choose = 3;
			else if (!((pos.y-aim.y)<4))
				choose = 2;
			else if (!((aim.x - pos.x) < 4))
				choose = 4;
			else if (!((aim.y - pos.y) < 4))
				choose = 1;
		}
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

void Hero::specialAttack(cocos2d::Vec2 target)
{
}


void Hero::setai()
{
	isai = true;
}

bool Hero::isAI() const
{
	if(this!=nullptr)
		return isai;
}

int Hero::getEnergy() const
{
	return energy;
}


bool Hero::isPoisoning() const
{
	return _isPoisoning;
}

void Hero::getPoisoning(float dlt)
{
	if (_isPoisoning)
	{
		_isfighting = 5;
		getHurt(static_cast<int>(MaxCurrentHP * SMOKE_ATK_COEFFICIENT));
		if (!this->isAI())
		{
			log("get poisoning");
			log("current hp:%d", _HP);
		}
	}

}

void Hero::setPoisoning(bool flag)
{
	if (flag)
		_isPoisoning++;
	else
		_isPoisoning--;
	if (!this->isAI())
	{
		log("current poisoning num : %d", _isPoisoning);
	}
}





void Hero::getHurt(int hurt)
{
	_isfighting = 5;
	if (_HP > hurt)
		_HP -= hurt;
	else
	{
		_HP = 0;
		_isAlive = false;
	}
}

void Hero::die()
{
	for (int i = 0; i < diamondNum; i++)
	{
		this->createDiamond();
	}
	if (!isai)
	{
		auto parent = dynamic_cast<MapLayer*>(getParent());
		parent->setalive(_isAlive);
	}
	this->removeFromParentAndCleanup(true);
}

void Hero::createDiamond()
{
	auto dia = Diamond::create("diamond.png");
	getParent()->addChild(dia);
	dia->setPosition(getPosition()+ Vec2(random(-10, 10), random(-10, 10)));
	log("treasure position:(%f,%f)", this->getPosition().x, this->getPosition().y);
	//dia->runAction(MoveTo::create(0.01, getPosition() + getParent()->getPosition()+Vec2(random(-25,25), random(-25, 25))));
	//加随机数避免宝石位置重叠
	dia->run_action();
	log("dia position:(%f,%f)", dia->getPosition().x, dia->getPosition().y);
}

void Hero::outofFighting(float dlt)
{
	if (_isfighting > 0)
		_isfighting--;
	if (!this->isAI())
		log("fighting- ,now:%d ", _isfighting);
}

int Hero::getBulletNum()
{
	return bulletNum;
}
