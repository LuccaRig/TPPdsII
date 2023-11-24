#include "Enemies.h"

Enemies::Enemies(){
    horde_number_ = 0;
    enemy_count_ = 6;
    boss_turns_ = 0;
}

Enemies::~Enemies() {
    for(int i=0; i<this->hordeSize(); ++i) {
        enemies_[i].reset();
    }
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

bool Enemies::bossIsAlive() {
    if(boss_turns_ > 0) return true;
    else return false;
}

void Enemies::deleteMonsterPool() {
    enemies_.clear();
}

Monster* Enemies::getMonsterInPosition(int position_x, int position_y){
    for(int i=0;i<enemy_count_;++i){
        if((this->enemy(i)->get_monster_position_x() == position_x) &&
            (this->enemy(i)->get_monster_position_y() == position_y) &&
            !this->enemy(i)->monsterIsDead()){
                return this->enemy(i);
            }
    }
    return nullptr;
}

void Enemies::bossTurnIncrement() {
    boss_turns_++;
}

void Enemies::eyeSpawn() {
    if(!(boss_turns_%2)){
    enemy_count_++;
    enemies_.push_back(std::unique_ptr<Monster>(new Monster("unholy skull")));
    }
}


Monster* Enemies::enemy(int enemy_number) {
    return enemies_[enemy_number].get();
}

void Enemies::setAllInStartPosition(Hero &rogue, Hero &mage, Hero &knight) {
    for(int i=0; i < this->hordeSize();++i){
        if(i < 2) this->enemy(i)->set_monster_position_x(i*2);
        if(i == 2) this->enemy(i)->set_monster_position_x(4);
        if(i > 2){
            this->enemy(i)->set_monster_position_y(4);
            if(i == 3) this->enemy(i)->set_monster_position_x(0);
            if(i == 4) this->enemy(i)->set_monster_position_x(2);
            if(i == 5) this->enemy(i)->set_monster_position_x(4);
            
        }
    }
    rogue.set_hero_position_x(3);
    rogue.set_hero_position_y(2);
    mage.set_hero_position_x(1);
    mage.set_hero_position_y(2);
    knight.set_hero_position_x(2);
    knight.set_hero_position_y(2);
}

bool Enemies::allEnemiesAreDead() {
    for(int i=0;i<enemy_count_;i++) {
        if(!this->enemy(i)->monsterIsDead()) return false;
    }
    return true;
}

void Enemies::createHordeEnemies(Hero &rogue, Hero &mage, Hero &knight) {
    if(horde_number_ == 0){
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("unholy skull")));
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("virulent wight")));
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("sand golem")));
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("ghastly beholder")));
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("bloody abomination")));
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("death knight")));
        setAllInStartPosition(rogue, mage, knight);
        this->hordePass();
    }
    if(horde_number_ == 1 && this->allEnemiesAreDead()){
        this->deleteMonsterPool();
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("unholy skull")));
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("virulent wight")));
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("sand golem")));
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("ghastly beholder")));
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("bloody abomination")));
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("death knight")));
        setAllInStartPosition(rogue, mage, knight);
        this->hordePass();
    }
    if(horde_number_ == 2 && this->allEnemiesAreDead()){
        this->deleteMonsterPool();
        enemy_count_ = 1;
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("BOSS")));
        setAllInStartPosition(rogue, mage, knight);
        boss_turns_++;
        horde_number_++;
    }
}
