#include <string>

#include "Monster.h"
#include "Board.h"
#include "Item.h"
#include "Hero.h"


    Monster::Monster (std::string monster_type) 
    {
        if (monster_type_ == "murky slaad")
        {
            monster_hp_ = 40;
            monster_dmg_ = 4;
            monster_exp_drop_ = 5;
            Monster::decideMonsterItem();
        }
        else if (monster_type_ == "poison drake")
        {
             monster_hp_ = 18;
            monster_dmg_ = 10;
            monster_exp_drop_ = 8;
            Monster::decideMonsterItem();
        }
        else if (monster_type_ == "hungry mimic")
        {
             monster_hp_ = 12;
            monster_dmg_ = 10;
            monster_exp_drop_ = 1;
            Monster::decideMonsterItem();
        }
        else if (monster_type_ == "ghastly beholder")
        {
             monster_hp_ = 25;
            monster_dmg_ = 5;
            monster_exp_drop_ = 1;
            Monster::decideMonsterItem();
        }
        else if (monster_type_ == "clawed abomination")
        {
             monster_hp_ = 20;
            monster_dmg_ = 15;
            monster_exp_drop_ = 1;
            Monster::decideMonsterItem();
        }
    }

    void Monster::moveThisMonster(Board tabuleiro)
    {
        std::vector<int> position = tabuleiro.findHeroPosition();
        tabuleiro.monsterMoveInBoard(monster_type_, position);

    }

    void Monster::attackHero(Hero heroi) 
    {
        heroi.modify_hero_hp(monster_dmg_);
    }

    void Monster::monsterGetDamaged(int dano) 
    {
        monster_hp_ += dano;
    }

    void Monster::decideMonsterItem()
    {
        Item mItem;
        monster_item_ = mItem.returnsRandomItem();
    }

    bool Monster::monsterIsDead()
    {
        if (monster_hp_>0) 
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    int Monster::returnExpDrop() 
    {
        return monster_exp_drop_;
    }
