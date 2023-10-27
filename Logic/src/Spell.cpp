#include <string>

#include "Spell.h"

Spell::Spell(int type)
{
    if (type == 1)
        spell_type_ = "knightSpell";
    else if (type == 2)
        spell_type_ = "rogueSpell";
    else if (type == 3)
        spell_type_ = "mageSpell";
    else if (type == 4)
        spell_type_ = "bossSpell";
}

Spell::~Spell()
{

}

void Spell::GetSpellsTraits()
{
    if (spell_type_ == "knightSpell"){
        spellStatus.hp += 5;
    }
    else if (spell_type_ == "rogueSpell"){
        spellStatus.attack += 2;
    }
}