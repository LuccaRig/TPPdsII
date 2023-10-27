#include "Skill.h"

Skill::Skill(std::string type)
{
    skill_type_ = type;

    if (skill_type_ == "knight"){
        skillStatus.hp_ += 6;
        skillStatus.attack_ += 1;
        changed_target_hp_ = 0;
    }
    else if (skill_type_ == "rogue"){
        skillStatus.hp_ += 0;
        skillStatus.attack_ += 3;
        changed_target_hp_ = 1;
    }
    else if (skill_type_ == "mage"){
        skillStatus.hp_ += 0;
        skillStatus.attack_ += 0;
        changed_target_hp_ = 13;
    }
    else if (skill_type_ == "boss"){
        skillStatus.hp_ += 1;
        skillStatus.attack_ += 1;
        changed_target_hp_ = 6;
    }
}

Skill::~Skill()
{

}

int Skill::skill_heal()
{
    return skillStatus.hp_;
}

int Skill::skill_buff()
{
    return skillStatus.attack_;
}

int Skill::skill_damage()
{
    return changed_target_hp_;
}