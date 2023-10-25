#ifndef SPELL_H
#define SPELL_H

#include <string>

#include "Hero.h"

class Spell{
  public:
    
    /// @brief Constructor
    Spell(int type); //Atribui ao spell_type_ um inteiro

    /// @brief Destructor
    ~Spell();
    
    /// @brief Determina o que cada magia faz
    void SpellsTraits(std::string spell_type_);

  private:
    std::string spell_type_;
    int spell_damage_;
    int spell_effect_;

};

#endif