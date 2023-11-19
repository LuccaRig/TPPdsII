#ifndef ENEMIES_H_
#define ENEMIES_H_

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Monster.h"


class Enemies{
  public:
    Enemies();

    ~Enemies();

    int get_horde_number();

    void hordePass();

    void createHordeEnemies();

    int hordeSize();

    Monster* enemy(int enemy_number);

    void deleteMonsterPool();

  private:
    int horde_number_;
    int enemy_count_;
    std::vector<std::unique_ptr<Monster>> enemies_;
};


#endif //ENEMIES_H_