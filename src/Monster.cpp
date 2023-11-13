#include <string>

#include "Monster.h"
#include "Board.h"
#include "Item.h"
#include "Hero.h"


    Monster::Monster (std::string monster_type) 
    {
        if (monster_type_ == "bloody abomination")
        {
            monster_hp_ = 12;
            monster_dmg_ = 8;
            monster_exp_drop_ = 5;
            Monster::decideMonsterItem();
        }
        else if (monster_type_ == "death knight")
        {
             monster_hp_ = 20;
            monster_dmg_ = 6;
            monster_exp_drop_ = 8;
            Monster::decideMonsterItem();
        }
        else if (monster_type_ == "sand golem")
        {
             monster_hp_ = 40;
            monster_dmg_ = 2;
            monster_exp_drop_ = 1;
            Monster::decideMonsterItem();
        }
        else if (monster_type_ == "ghastly beholder")
        {
             monster_hp_ = 10;
            monster_dmg_ = 2;
            monster_exp_drop_ = 1;
            Monster::decideMonsterItem();
        }
        else if (monster_type_ == "unholy skull")
        {
             monster_hp_ = 10;
            monster_dmg_ = 4;
            monster_exp_drop_ = 1;
            Monster::decideMonsterItem();
        }
        else if (monster_type_ == "virulent wight")
        {
             monster_hp_ = 13;
            monster_dmg_ = 5;
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
      //  heroi.modify_hero_hp(monster_dmg_);
    }

    void Monster::set_monster_hp(int dano) 
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

    int Monster::get_exp_drop() 
    {
        return monster_exp_drop_;
    }

    int Monster::get_monster_position_x()
    {
        return monster_position_x_;
    }

     int Monster::get_monster_position_y()
    {
        return monster_position_y_;
    }

    void Monster::set_monster_position_x(int xi)
    {
        monster_position_x_ = xi;
    }
 
    void Monster::set_monster_position_y(int yi)
    {
        monster_position_y_ = yi;
    }