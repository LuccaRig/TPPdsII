#ifndef SPELL_H
#define SPELL_H

#include <string>

class Spell{
  public:
    
    /// @brief Constructor TODO: Atribui ao spell_type_ um inteiro
    Spell(int type);

    /// @brief Destructor
    ~Spell();
    
    /// @brief Determina o que cada magia faz
    void GetSpellsTraits();

  private:
    std::string spell_type_;
    
    struct spellStatus{
      int hp_;
      int attack_;
    };

};

#endif