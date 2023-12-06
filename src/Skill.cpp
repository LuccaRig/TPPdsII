#include <string>

#include "Skill.h"

Skill::Skill(std::string type, int skill_effect) 
{
    skill_hp_ = 0;
    skill_attack_ = 0;
    changed_target_hp_ = 0;
    skill_type_ = type;

    if (skill_type_ == "knight"){
        skill_hp_ += skill_effect;
        skill_attack_ += 0;
        changed_target_hp_ = 0;
    }
    else if (skill_type_ == "rogue"){
        skill_hp_ += 0;
        skill_attack_ += skill_effect;
        changed_target_hp_ = 0;
    }
    else if (skill_type_ == "mage"){
        skill_hp_ += 0;
        skill_attack_ += 0;
        changed_target_hp_ = skill_effect;
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