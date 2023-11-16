#ifndef HORDES_H_
#define HORDES_H_

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Monster.h"


class Hordes{
  public:
    Hordes();

    ~Hordes();

    int get_horde_number();

    void hordePass();

    void fillMonsterPool(Monster selected_enemy);

    void createHordeEnemies();

    Monster enemy(int enemy_number);

    void deleteMonsterPool();

  private:
    int horde_number_;
    int enemy_count_;
    std::vector<Monster> enemies_;
};


#endif //HORDES_H_