#include <string>

#include "Skill.h"

Skill::Skill(std::string type)
{
    skill_type_ = type;

    if (skill_type_ == "knight"){
        skill_hp_ += 6;
        skill_attack_ += 1;
        changed_target_hp_ = 0;
    }
    else if (skill_type_ == "rogue"){
        skill_hp_ += 0;
        skill_attack_ += 3;
        changed_target_hp_ = 1;
    }
    else if (skill_type_ == "mage"){
        skill_hp_ += 0;
        skill_attack_ += 0;
        changed_target_hp_ = 13;
    }
    else if (skill_type_ == "boss"){
        skill_hp_ += 1;
        skill_attack_ += 1;
        changed_target_hp_ = 6;
    }
}

Skill::~Skill()
{

}

int Skill::skill_heal()
{
    return skill_hp_;
}

int Skill::skill_buff()
{
    return skill_attack_;
}

int Skill::skill_damage()
{
    return changed_target_hp_;
}