#include "Enemies.h"

Enemies::Enemies(){
    horde_number_ = 0;
    enemy_count_ = 6;
}

Enemies::~Enemies()
{
}

int Enemies::get_horde_number()
{
    return horde_number_;
}

void Enemies::hordePass() {
    horde_number_++;
}

int Enemies::hordeSize() {
    return enemy_count_;
}

void Enemies::deleteMonsterPool() {
    enemies_.clear();
}

Monster* Enemies::enemy(int enemy_number) {
    return enemies_[enemy_number].get();
}

void Enemies::createHordeEnemies() {
    if(horde_number_ == 0){
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("unholy skull")));
        this->enemy(0)->set_monster_position_x(4);
        this->enemy(0)->set_monster_position_y(0);

    }
    if(horde_number_ == 1){
        // deleteMonsterPool();

        // Monster monster1("sand golem");
        // fillMonsterPool(monster1);
        // Monster monster2("ghastly beholder");
        // fillMonsterPool(monster2);
        // Monster monster3("sand golem");
        // fillMonsterPool(monster3);
        // Monster monster4("virulent wight");
        // fillMonsterPool(monster4);
        // Monster monster5("unholy skull");
        // fillMonsterPool(monster5);
        // Monster monster6("virulent wight");
        // fillMonsterPool(monster6);
    }
    if(horde_number_ == 2){
        deleteMonsterPool();

        //BOSS
    }
}
