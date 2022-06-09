#include "Smoke.h"

Smoke::Smoke()
{
}

Smoke::~Smoke()
{
}

Smoke* Smoke::create(const char* filename)
{
	Smoke* smoke = new Smoke();
	if (smoke && smoke->initWithFile(filename)&&smoke->init())
	{
		smoke->autorelease();
		return smoke;
	}
	CC_SAFE_DELETE(smoke);

	return nullptr;
}

bool Smoke::init()
{
	setTag(SMOKE_TAG);
	bindPhysicsBody();
	setOpacity(250);
	setAnchorPoint(Vec2(0, 0));
	_fadein = FadeIn::create(3.0f);
	_fadein->retain();
	this->retain();
	return true;
}

void Smoke::bindPhysicsBody()
{
	auto physicsBody = cocos2d::PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.0f, 1.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	physicsBody->setContactTestBitmask(1);
	physicsBody->setTag(SMOKE_TAG);
	this->setPhysicsBody(physicsBody);
}

void Smoke::RunfadeIn()
{
	this->runAction(_fadein);
}


