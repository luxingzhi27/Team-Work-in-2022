#pragma once
#ifndef _CONST_H_
#define _CONST_H_


////////////////人物相关
//people
#define HIGH_SPEED 0.8
#define NORMAL_SPEED 1.0
#define LOW_SPEED 1.2



#define AmplificationRate  0.2

//hero
#define MAX_BULLET_NUM 6
#define MAX_ENERGY 4
#define HERO_CONTACT_MASK 1
#define HERO_CATEGORY_MASK 1
#define HERO_TAG 1
enum class HeroTowards { front, back, right, left };

//Shirley
#define SHIRLEY_HP 4000
#define SHIRLEY_ATK 400
#define SHIRLEY_REACH 250
#define SHIRLEY_SPEED 1.1
#define SHIRLEY_MAX_ENERGY 8

#define SHIRLEY_SPELL_RATE 3
#define SHIRLEY_SPELL_REACH 400
#define SHIRLEY_SPELL_SPEED 1.3


//Colt
#define COLT_HP 5000
#define COLT_ATK 300
#define COLT_REACH 300
#define COLT_SPEED 1.0
#define COLT_MAX_ENERGY 6

#define COLT_SPELL_RATE 3.5
#define COLT_SPELL_REACH 500
#define COLT_SPELL_SPEED 0.9

//Leon
#define LEON_HP 4500
#define LEON_ATK 500
#define LEON_REACH 200
#define LEON_SPEED 1.2
#define LEON_MAX_ENERGY 10

#define LEON_SPELL_RATE 4
#define LEON_SPELL_REACH 1000
#define LEON_SPELL_SPEED 1.4

//Nita
#define NITA_HP 5000
#define NITA_ATK 250
#define NITA_REACH 350
#define NITA_SPEED 1.0
#define NITA_MAX_ENERGY 6

#define NITA_SPELL_RATE 3
#define NITA_SPELL_REACH 300
#define NITA_SPELL_SPEED 1.2


//////////////////物品相关
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

#define SMOKE_TAG 5
#define SMOKE_ATK_COEFFICIENT 0.05f

#define SPELL_TAG 6

enum class ContactEvents{HeroHurt,TreasureHurt,getDiamond, HeroPoisoning};


#endif