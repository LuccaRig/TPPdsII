#ifndef HERO_H
#define HERO_H

#include <string>

#include "Board.h"
#include "Spell.h"

class Hero{
  public:

    /// @brief Constructor TODO: Atribui os status para cada hero_type_, assim como o spell_type_
    Hero(std::string type);

    /// @brief Destructor
    ~Hero();

    /// @brief Move o herói para um número determinado de casas adjacentes
    void HeroMove();

    /// @brief Ataca uma das 4 casas adjacentes ao herói
    void HeroAttack();

    /// @brief Utiliza a habilidade especial do herói
    void CastSpell();

    /// @brief Retorna o nível do herói
    int current_lvl();

    /// @brief Aumenta o nível do herói
    void LvlUp(int Exp);

  private:
    struct Status{
        int hp;
        int attack;
        int special_attack;
    };
    int exp;
    std::string hero_type;
    Spell spell_type;
};

#endif