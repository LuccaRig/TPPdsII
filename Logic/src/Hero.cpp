#include "Hero.h"

Hero::Hero(std::string type)
{
    hero_type_ = type;

    if (hero_type_ == "knight") {
        Status.hp_ = 25;
        Status.attack_ = 7;
        Status.special_attack_ = 5;
        skill_type_(knight);
    }
    else if (hero_type_ == "rogue"){
        Status.hp_ = 10;
        Status.attack_ = 12;
        Status.special_attack_ = 5;
        skill_type_(rogue);
    }
    else if (hero_type_ == "mage"){
        Status.hp_ = 15;
        Status.attack_ = 5;
        Status.special_attack_ = 15;
        skill_type_(mage);
    }
}

Hero::~Hero()
{

}

int Hero::current_hero_hp()
{
    return Status.hp_;
}

void Hero::modify_hero_hp(int changed_hp)
{
    Status.hp_ += changed_hp;
}

void Hero::HeroMove()
{

}

void Hero::HeroAttack()
{

}

void Hero::UseSkill()
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

void Hero::LvlUp(int lvl)
{
    
}