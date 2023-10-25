#ifndef MONSTER_H
#define MONSTER_H

#include <string>

#include "Board.h"
#include "Tile.h"
#include "Itens.h"
// #include "Hero.h"

class Monster {
  
  public:

    /// @brief construtor
    Monster(int monster_type_);

    /// @brief destrutor
    ~Monster();
    
    /// @brief movimenta o monstro para uma posição mais próxima de um herói. PRECONDIÇÃO: monstro não está a alcance de ataque
    void move_this_monster();

    /// @brief ataca o herói. PRECONDIÇÃO: monstro está a alcance de ataque
    void attack_hero();

    /// @brief determina se um item será deixado pelo monstro e qual.
    void decide_monster_item();

    /// @return retorna 1 se o monstro estiver morto e 0 se não estiver.
    bool monster_is_dead();

    /// @return retorna o número de experiência que o monstro dará quando for derrotado
    int return_exp_drop();



  private:
    std::string monster_type_;
    int monster_hp_;
    int monster_dmg_;
    int monster_exp_drop_;
    int monster_item_drop_;


};

#endif
