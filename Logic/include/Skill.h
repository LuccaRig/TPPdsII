#ifndef SKILL_H
#define SKILL_H

#include <string>

class Skill{
  public:
    
    /// @brief Constructor
    Skill(std::string type);

    /// @brief Destructor
    ~Skill();

  private: 
    struct skillStatus{
      int hp_;
      int attack_;
    };

    std::string skill_type_;
};

#endif