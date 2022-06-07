#pragma once
#ifndef _CONST_H_
#define _CONST_H_


////////////////�������
//people
#define HIGH_SPEED 0.8
#define NORMAL_SPEED 1.0
#define LOW_SPEED 1.2



#define AmplificationRate  1.1

//hero
//#define LEVEL_UP_ATK 400
//#define LEVEL_UP_HP 2000
#define MAX_BULLET_NUM 6
//#define MAX_ENERGY 4
#define HERO_CONTACT_MASK 1
#define HERO_CATEGORY_MASK 1
#define HERO_TAG 1
enum class HeroTowards { front, back, right, left };

//Shirley
#define SHIRLEY_HP 4000
#define SHIRLEY_ATK 500
#define SHIRLEY_REACH 250
#define SHIRLEY_SPEED 1.2
#define SHIRLEY_MAX_ENERGY 4



//////////////////��Ʒ���
#define TreasureHP 4000
#define TREASURE_TAG 2
#define TREASURE_CONTACT_MASK 3
#define TREASURE_CATEGORY_MASK 3

#define DIAMOND_CONTACT_MASK 3
#define DIAMOND_CATEGORY_MASK 3
#define DIAMOND_TAG  3

#define BULLET_TAG 4
#define BULLET_CONTACT_MASK 3
#define BULLET_CATEGORY_MASK 3

enum class ContactEvents{HeroHurt,TreasureHurt,getDiamond};


#endif