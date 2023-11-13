#ifndef SKILL_H_
#define SKILL_H_

#include <string>

class Skill{

  public:
    
    /// @brief Constructor
    Skill(std::string type, int skill_effect);

    /// @brief Destructor
    ~Skill();

    /// @return Retorna os status de cura da habilidade
    int skill_heal();

    /// @return Retorna os status de aumento de ataque da habilidade
    int skill_buff();

    /// @return Retorna o dano que a habilidade causa
    int skill_damage();

  private: 
    int skill_hp_;
    int skill_attack_;
    int changed_target_hp_;
    std::string skill_type_;
};

#endif // SKILL_H_