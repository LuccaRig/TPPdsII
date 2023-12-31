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

int Enemies::get_horde_number() {
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

void Enemies::randomEyeSelect() {
    int random_selec = rand()%2;
    if(random_selec == 0) enemies_.push_back(std::unique_ptr<Monster>(new Monster("bloodshot eye")));
    if(random_selec == 1) enemies_.push_back(std::unique_ptr<Monster>(new Monster("ocular watcher")));
}


std::pair<int, int> Enemies::randomPositionSpawn(Board* my_board) {
    srand((unsigned) time(NULL));
    int random_position_x = rand()%5;
    int random_position_y = rand()%5;
    return std::make_pair(random_position_x, random_position_y);
}

void Enemies::eyeSpawn(Board* my_board) {
    if(boss_turns_){
        int pos_x = this->randomPositionSpawn(my_board).first;
        int pos_y = this->randomPositionSpawn(my_board).second;
        enemy_count_++;
        this->randomEyeSelect();
        while(!(my_board->get_tile_at(pos_x, pos_y)->moveableTile()) ||
             (my_board->get_tile_at(pos_x, pos_y)->getObjectInTile() == "item")) {
            pos_x = this->randomPositionSpawn(my_board).first;
            pos_y = this->randomPositionSpawn(my_board).second;
        }
        (*enemies_[enemy_count_-1]).set_monster_position_x(pos_x);
        (*enemies_[enemy_count_-1]).set_monster_position_y(pos_y);
    }
}


Monster* Enemies::enemy(int enemy_number) {
    return enemies_[enemy_number].get();
}

void Enemies::setAllInStartPosition(std::vector<std::unique_ptr<Item>> &itens, Board* my_board, Hero &rogue, Hero &mage, Hero &knight) {
    for(int i=0;i<5;i++) {
        for(int j=0;j<5;j++) {
            my_board->get_tile_at(i, j)->deleteObjectInTile();
        }
    }
    for(auto it = itens.begin(); it != itens.end(); it++) {
        (*it)->set_item_to_used();
    }
    if(horde_number_ < 2) {
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
    else{
        this->enemy(0)->set_monster_position_x(2);
        this->enemy(0)->set_monster_position_y(0);

        rogue.set_hero_position_x(3);
        rogue.set_hero_position_y(4);
        mage.set_hero_position_x(1);
        mage.set_hero_position_y(4);
        knight.set_hero_position_x(2);
        knight.set_hero_position_y(4);
    }
}

bool Enemies::allEnemiesAreDead() {
    for(int i=0;i<enemy_count_;i++) {
        if(!this->enemy(i)->monsterIsDead()) return false;
    }
    return true;
}

void Enemies::createHordeEnemies(std::vector<std::unique_ptr<Item>> &itens, Board* my_board, Hero &rogue, Hero &mage, Hero &knight) {
    if(horde_number_ == 0){
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("virulent wight 1")));
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("stalker")));
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("unholy skull 1")));
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("unholy skull 2")));
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("floating eye")));
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("virulent wight 2")));
        setAllInStartPosition(itens, my_board, rogue, mage, knight);
        this->hordePass();
    }
    if(horde_number_ == 1 && this->allEnemiesAreDead()){
        this->deleteMonsterPool();
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("bloody abomination 1")));
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("sand golem")));
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("bloody abomination 2")));
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("ghastly beholder 1")));
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("death knight")));
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("ghastly beholder 2")));
        setAllInStartPosition(itens, my_board, rogue, mage, knight);
        this->hordePass();
    }
    if(horde_number_ == 2 && this->allEnemiesAreDead()) {
        this->deleteMonsterPool();
        enemy_count_ = 1;
        enemies_.push_back(std::unique_ptr<Monster>(new Monster("BOSS")));
        setAllInStartPosition(itens, my_board, rogue, mage, knight);
        boss_turns_++;
        horde_number_++;
    }
}
