#include "Article.h"

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in originalHelloWorldScene.cpp\n");
}

Treasure::Treasure()
{
}

Treasure::~Treasure()
{
}

Treasure* Treasure::create(const char* filename)
{
	Treasure* treasure = new Treasure();
	if (treasure && treasure->initWithFile(filename)&&treasure->Treasure::init())
	{
		treasure->autorelease();
		return treasure;
	}
	CC_SAFE_DELETE(treasure);
	return nullptr;
}

bool Treasure::init()
{
	this->_HP = TreasureHP;
	this->setTag(TREASURE_TAG);
	bindPhysicsBody();
	return true;
}

int Treasure::getHP() const
{
	return _HP;
}

void Treasure::getHurt(int hurt)
{
	if (_HP > hurt)
	{
		_HP -= hurt;
		auto fadeout = FadeOut::create(0.05f);
		auto fadein = FadeIn::create(0.05f);
		this->runAction(Sequence::create(fadeout, fadein, nullptr));
	}
	else
	{
		_HP = 0;
		_isDestroyed = true;
		auto fadeout = FadeOut::create(0.1f);
		auto fadein = FadeIn::create(0.1f);
		this->runAction(Sequence::create(fadein, fadeout,fadein->clone(),fadeout->clone(), nullptr));
		this->createDiamond();
		this->removeFromParentAndCleanup(true);
	}
}


void Treasure::createDiamond()
{
	auto dia = Diamond::create("diamond.png");
	
	this->getParent()->addChild(dia,10);
	log("treasure position:(%f,%f)", this->getPosition().x, this->getPosition().y);
	dia->setPosition(getPosition());
	dia->run_action();
	log("dia position:(%f,%f)", dia->getPosition().x, dia->getPosition().y);
}

void Treasure::bindPhysicsBody()
{
	auto physicsBody = cocos2d::PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.0f, 1.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	physicsBody->setContactTestBitmask(TREASURE_CONTACT_MASK);
	physicsBody->setCategoryBitmask(TREASURE_CATEGORY_MASK);
	physicsBody->setTag(TREASURE_TAG);
	this->setPhysicsBody(physicsBody);
}

bool Treasure::isDestroyed()
{
	return _isDestroyed;
}


////////////////////////////////////////////////////////////////////


Diamond::Diamond()
{
}

Diamond::~Diamond()
{
}

Diamond* Diamond::create(const char* filename)
{
	Diamond* diamond = new Diamond();
	if (diamond && diamond->initWithFile(filename)&&diamond->Diamond::init())
	{
		diamond->autorelease();

		return diamond;
	}
	CC_SAFE_DELETE(diamond);
	return nullptr;
}

bool Diamond::init()
{

	this->setAppear();
	this->setShining();
	this->setTag(DIAMOND_TAG);
	//this->scheduleUpdate();
	bindPhysicsBody();
	return true;
}

void Diamond::run_action()
{
	this->runAction(_Appear);
	this->runAction(DelayTime::create(0.6f));
	this->runAction(_Shining);
}

void Diamond::setPosition(Vec2 Pos)
{
	this->Node::setPosition(Pos.x + random(-30, 30), Pos.y + random(-30, 30));
	log("setposition succeed");
}

void Diamond::bindPhysicsBody()
{
	auto physicsBody = cocos2d::PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.0f, 1.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	physicsBody->setContactTestBitmask(TREASURE_CONTACT_MASK);
	physicsBody->setCategoryBitmask(TREASURE_CATEGORY_MASK);
	physicsBody->setTag(DIAMOND_TAG);
	this->setPhysicsBody(physicsBody);
}


void Diamond::setAppear()
{auto fade_in = FadeIn::create(0.3f);
	auto moveby_up = MoveBy::create(0.3f, Vec2(0, this->getContentSize().height/2));
	auto moveby_down = moveby_up->reverse();
	auto spawn = Spawn::create(fade_in, moveby_up, nullptr);
	this->_Appear = Sequence::create(spawn,moveby_down, nullptr);
	
}

void Diamond::setShining()
{
	auto fade_in = FadeIn::create(0.3f);
	auto delay = DelayTime::create(0.3f);
	auto fade_out = FadeOut::create(0.3f);
	auto Shining = Sequence::create(fade_in, delay, fade_out, nullptr);
	_Shining = RepeatForever::create(Shining);
}

