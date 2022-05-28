#include "people.h"
#include"cocos2d.h"
USING_NS_CC;

#define MOVEDURATION 0.01
#define DISTANCE 1
#define UP Vec2(0,DISTANCE)
#define DOWN Vec2(0,-DISTANCE)
#define LEFT Vec2(-DISTANCE,0)
#define RIGHT Vec2(DISTANCE,0)



People::~People()
{
}

void People::bindSprite(Sprite* sprite)
{
	m_hero = sprite;
	this->addChild(m_hero);
}


void People::move_L()
{
	auto move = MoveTo::create(MOVEDURATION, LEFT);
	this->runAction(move);
}

void People::move_R()
{
	auto move = MoveTo::create(MOVEDURATION, RIGHT);
	this->runAction(move);
}

void People::move_U()
{
	auto move = MoveTo::create(MOVEDURATION, UP);
	this->runAction(move);
}

void People::move_D()
{
	auto move = MoveTo::create(MOVEDURATION, DOWN);
	this->runAction(move);
}

void People::move_LU()
{
	auto move = MoveTo::create(MOVEDURATION, LEFT+UP);
	this->runAction(move);
}

void People::move_LD()
{
	auto move = MoveTo::create(MOVEDURATION, LEFT+DOWN);
	this->runAction(move);
}

void People::move_RU()
{
	auto move = MoveTo::create(MOVEDURATION, RIGHT+UP);
	this->runAction(move);
}

void People::move_RD()
{
	auto move = MoveTo::create(MOVEDURATION, RIGHT+DOWN);
	this->runAction(move);
}
