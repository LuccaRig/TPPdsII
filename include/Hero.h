#ifndef HERO_H
#define HERO_H

#include <string>

class Hero{
private:
    struct Status{
        int HP;
        int Attack;
        int Defense;
        int SpecialAttack;
    };
    int Exp;
    std::string HeroType;

public:

    /// @brief Constructor
    Hero(std::string Type);

    /// @brief Destructor
    ~Hero();

    /// @brief Ataca uma das 4 casas adjacentes ao herói
    void heroAttack();

    /// @brief Utiliza a habilidade especial do herói
    void heroSpell();

    /// @brief Determina o nível do herói
    int currentLvl();

    /// @brief Aumenta o nível do herói
    void lvlUp(int Exp);

};

#endif