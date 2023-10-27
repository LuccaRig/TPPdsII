#ifndef SKILL_H
#define SKILL_H

#include <string>

class Skill{
  public:
    
    /// @brief Constructor
    Skill(std::string type);

    /// @brief Destructor
    ~Skill();

    /// @brief Retorna os status de cura da habilidade
    int skill_heal();

    /// @brief Retorna os status de aumento de ataque da habilidade
    int skill_buff();

    /// @brief Retorna o dano que a habilidade causa
    int skill_damage();

  private: 
    struct skillStatus{
      int hp_;
      int attack_;
    };

    std::string skill_type_;

    int changed_target_hp_;
};

#endif