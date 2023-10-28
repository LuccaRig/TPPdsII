#ifndef HERO_H
#define HERO_H

#include <string>

#include "Board.h"
#include "Skill.h"

class Hero{
  public:

    /// @brief Constructor TODO: Atribui os status para cada hero_type_, assim como o spell_type_
    Hero(std::string type);

    /// @brief Destructor
    ~Hero();

    /// @brief Retorna a vida do herói
    int current_hero_hp();

    /// @brief Altera o hp atual do herói
    void modify_hero_hp(int changed_hp);

    /// @brief Move o herói para um número determinado de casas adjacentes
    void HeroMove();

    /// @brief Ataca uma das 4 casas adjacentes ao herói
    void HeroAttack();

    /// @brief Utiliza a habilidade especial do herói
    void UseSkill();

    /// @brief Retorna o nível do herói
    int current_lvl(int Exp);

    /// @brief Aumenta o nível do herói
    void LvlUp(int lvl);

  private:
    struct Status{
        int hp_;
        int attack_;
        int special_attack_;
    };

    std::string hero_type_;

    int exp_;
    
    Skill skill_type_;
};

#endif