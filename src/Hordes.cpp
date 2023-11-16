#include "Hordes.h"

Hordes::Hordes(){
    horde_number_ = 0;
    enemy_count_ = 6;
}

Hordes::~Hordes()
{
}

int Hordes::get_horde_number()
{
    return horde_number_;
}

void Hordes::hordePass() {
    horde_number_++;
}

void Hordes::fillMonsterPool(Monster selected_enemy) {
    enemies_.push_back(selected_enemy);
}

void Hordes::deleteMonsterPool() {
    enemies_.clear();
}

Monster Hordes::enemy(int enemy_number) {
    return enemies_[enemy_number];
}

void Hordes::createHordeEnemies() {
    if(horde_number_ == 0){
        Monster monster1("bloody abomination");
        monster1.set_monster_position_x(0);
        monster1.set_monster_position_y(0);
        fillMonsterPool(monster1);

        Monster monster2("ghastly beholder");
        monster2.set_monster_position_x(2);
        monster2.set_monster_position_y(0);
        fillMonsterPool(monster2);


        Monster monster3("unholy skull");
        monster3.set_monster_position_x(4);
        monster3.set_monster_position_y(0);
        fillMonsterPool(monster3);


        Monster monster4("virulent wight");
        monster4.set_monster_position_x(0);
        monster4.set_monster_position_y(4);
        fillMonsterPool(monster4);


        Monster monster5("unholy skull");
        monster5.set_monster_position_x(2);
        monster5.set_monster_position_y(4);
        fillMonsterPool(monster5);


        Monster monster6("virulent wight");
        monster6.set_monster_position_x(4);
        monster6.set_monster_position_y(4);
        fillMonsterPool(monster6);
    }
    if(horde_number_ == 1){
        deleteMonsterPool();

        Monster monster1("sand golem");
        fillMonsterPool(monster1);
        Monster monster2("ghastly beholder");
        fillMonsterPool(monster2);
        Monster monster3("sand golem");
        fillMonsterPool(monster3);
        Monster monster4("virulent wight");
        fillMonsterPool(monster4);
        Monster monster5("unholy skull");
        fillMonsterPool(monster5);
        Monster monster6("virulent wight");
        fillMonsterPool(monster6);
    }
    if(horde_number_ == 2){
        deleteMonsterPool();

        //BOSS
    }
}
