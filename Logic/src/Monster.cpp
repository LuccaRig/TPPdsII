#include "Monster.h"



    void Monster::moveThisMonster()
    {
        Board mBoard;
        mBoard.monsterMoveInBoard(monster_type_, 1, 1);

    }

    void Monster::attackHero(Hero heroi) 
    {
        // heroi.heroGetDamaged(monster_dmg_)
    }

    void Monster::monsterGetDamaged(int dano) 
    {
        monster_hp_ -= dano;
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
