#include "Hero.h"

Hero::Hero(std::string type)
{
    hero_type_ = type;

    if (hero_type_ == "knight") {
        Status.hp_ = 25;
        Status.attack_ = 5;
        Status.special_attack_ = 5;
    }
    else if (hero_type_ == "rogue"){
        Status.hp_ = 10;
        Status.attack_ = 10;
        Status.special_attack_ = 5;
    }
    else if (hero_type_ == "mage"){
        Status.hp_ = 15;
        Status.attack_ = 5;
        Status.special_attack_ = 15;
    }
}

Hero::~Hero()
{

}

void Hero::HeroMove()
{

}

void Hero::HeroAttack()
{

}

void Hero::CastSpell()
{

}

int Hero::current_lvl(int experience)
{
    exp_ = experience;

    if (exp_ < 12)
        return 1;
    else if (exp_ < 25)
        return 2;
    else if (exp_ < 37)
        return 3;
    else if (exp_ < 50)
        return 4;
    else {
        return 5;
    }
}

void Hero::LvlUp()
{
    
}