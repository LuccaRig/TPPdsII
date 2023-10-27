#include "Skill.h"

Skill::Skill(std::string type)
{
    skill_type_ = type;

    if (skill_type_ == "knight")
        skillStatus.hp_ += 6;
    else if (skill_type_ == "rogue")
        skillStatus.attack_ += 3;
    else if (skill_type_ == "mage")
        skillStatus.hp_ -= 13;
    else if (skill_type_ == "boss")
        skillStatus.hp_ -= 6;
}

Skill::~Skill()
{

}