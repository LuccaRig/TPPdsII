#include <string>

#include "Hero.h"
#include "Monster.h"
#include "Skill.h"
#include "Item.h"

Hero::Hero(std::string type)
{
    exp_ = 0;
    hero_type_ = type;

    if (hero_type_ == "knight") {
        hero_hp_ = 25;
        hero_attack_ = 7;
        hero_special_attack_ = 5;
        skill_type_("knight");
    }
    else if (hero_type_ == "rogue"){
        hero_hp_ = 10;
        hero_attack_ = 12;
        hero_special_attack_ = 5;
        skill_type_("rogue");
    }
    else if (hero_type_ == "mage"){
        hero_hp_ = 15;
        hero_attack_ = 5;
        hero_special_attack_ = 15;
        skill_type_("mage");
    }
}

Hero::~Hero()
{

}

int Hero::current_hero_hp()
{
    return hero_hp_;
}

void Hero::modify_hero_hp(int changed_hp)
{
    hero_hp_ += changed_hp;
}

void Hero::HeroMove()
{

}

void Hero::HeroAttack()
{

}
    /// TODO: implementar a vida tirada do alvo
void Hero::UseSkill()
{
    hero_hp_ += skill_type_.skill_heal();
    hero_attack_ += skill_type_.skill_buff();
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