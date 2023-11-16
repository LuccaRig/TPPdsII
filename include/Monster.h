#ifndef MONSTER_H_
#define MONSTER_H_

#include <string>

#include "Board.h"
#include "Tile.h"
#include "Item.h"
#include "Hero.h"

class Monster {
  
  public:

    /// @brief contrói monstros com diferentes características dependendo do tipo de monstro recebido
    Monster(std::string monster_type_);

    /// @brief destrutor
    ~Monster();

    /// @brief ataca o herói. PRECONDIÇÃO: algum herói está a alcance de ataque 
    void attackHero(Hero);

    /// @brief  adiciona o valor recebido em pontos de vida para o monstro. PRECONDIÇÃO: parâmetro deve ser valor negativo 
    /// @param  attack_ do herói
    void set_monster_hp(int);

    /// @return retorna true se o monstro estiver morto e false se não estiver.
    bool monsterIsDead();

    /// @return retorna o número de experiência que o monstro dará quando for derrotado
    int get_exp_drop();

    /// @return retorna a coordenada x do monstro
    int get_monster_position_x();

    /// @return retorna a coordenada y do monstro
    int get_monster_position_y();

    /// @brief substitui a coordenada x do monstro pelo valor do parâmetro
    void set_monster_position_x(int xi);

    /// @brief substitui a coordenada y do monstro pelo valor do parâmetro
    void set_monster_position_y(int yi);



    // aqui será construído um item e monster_item_drop_ será igualado à função returns_random_item
  private:
    std::string monster_type_;
    int monster_hp_;
    int monster_dmg_;
    int monster_exp_drop_;
    std::string monster_item_;
    int monster_position_x_;
    int monster_position_y_;


};

#endif // MONSTER_H_