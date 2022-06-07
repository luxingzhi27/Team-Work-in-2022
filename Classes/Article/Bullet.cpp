#include "Bullet.h"
Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

Bullet* Bullet::create(const char* filename)
{
	Bullet* bullet = new Bullet();
	if (bullet && bullet->initWithFile(filename)&&bullet->init())
	{
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

bool Bullet::init()
{
	
	setTag(BULLET_TAG);
	bindPhysicsbody();
	return true;
}

void Bullet::setAttributes(int atk, int reach, float speed)
{
	_ATK = atk;
	_Reach = reach  ;
	_FlyingSpeed = speed;
}


int Bullet::getATK()
{
	return _ATK;
}

void Bullet::setType(const char* filename)
{
	_Type = filename;
}



void Bullet::onHit()
{
	auto SpecialEffect = cocos2d::ParticleExplosion::create();
	SpecialEffect->setDuration(0.3f);
	SpecialEffect->setStartColor(cocos2d::Color4F::WHITE);
	SpecialEffect->setEndColor(cocos2d::Color4F::RED);
	SpecialEffect->setStartColorVar(cocos2d::Color4F::BLACK);
	SpecialEffect->setEndColorVar(cocos2d::Color4F::BLACK);
	SpecialEffect->setScale(0.18f);
	SpecialEffect->setSpeed(700);
	SpecialEffect->setLife(0.1);
	SpecialEffect->setLifeVar(0.05);
	SpecialEffect->setPosition(this->getPosition().x+25,this->getPosition().y+25);
	this->getParent()->addChild(SpecialEffect, 10);
	log("firework,%D,%D",SpecialEffect->getPosition().x, SpecialEffect->getPosition().y);
	this->removeFromParentAndCleanup(true);
}

void Bullet::fillenergy()
{
	_hero->fillEnergy();
}

void Bullet::bindPhysicsbody()
{
	auto physicsBody = cocos2d::PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.0f, 1.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	physicsBody->setContactTestBitmask(BULLET_CONTACT_MASK);
	physicsBody->setCategoryBitmask(BULLET_CATEGORY_MASK);
	physicsBody->setTag(BULLET_TAG);
	this->addComponent(physicsBody);
}

void Bullet::bindHero(Hero* hero)
{
	_hero = hero;
}