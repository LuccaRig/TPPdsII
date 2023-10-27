#ifndef MONSTER_H
#define MONSTER_H

#include <string>

#include "Board.h"
#include "Tile.h"
#include "Item.h"
#include "Hero.h"

class Monster {
  
  public:

    /// @brief construtor
    Monster(std::string monster_type_);

    /// @brief destrutor
    ~Monster();
    
    /// @brief movimenta o monstro para uma posição mais próxima de um herói. PRECONDIÇÃO: nenhum herói está a alcance de ataque
    void moveThisMonster();

    /// @brief ataca o herói. PRECONDIÇÃO: algum herói está a alcance de ataque 
    void attackHero(Hero);

    /// @brief  permite que o monstro perca pontos de vida
    /// @param  dano recebido
    void monsterGetDamaged(int);

    /// @brief determina se um item será deixado pelo monstro e qual.
    void decideMonsterItem();

    /// @return retorna true se o monstro estiver morto e false se não estiver.
    bool monsterIsDead();

    /// @return retorna o número de experiência que o monstro dará quando for derrotado
    int returnExpDrop();


    // aqui será construído um item e monster_item_drop_ será igualado à função returns_random_item
  private:
    std::string monster_type_;
    int monster_hp_;
    int monster_dmg_;
    int monster_exp_drop_;
    std::string monster_item_;


};

#endif
