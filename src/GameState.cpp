#include "GameState.h"

GameState::GameState(){
    monster_turn_count_ = 0;
}

GameState::~GameState() {
}

void GameState::gameStart() {
}

void GameState::heroTurnPass() {
    hero_turn_count_++;
}

bool GameState::isPlayerTurn() {
    if(hero_turn_count_ < 9){
        return true;
    }
    else{
        return false;
    }
    
}

std::string GameState::whichHeroTurn(){
    if(hero_turn_count_ == 0 || hero_turn_count_ == 3 || hero_turn_count_ == 6){
        return "rogue";
    }
    else if(hero_turn_count_ == 1 || hero_turn_count_ == 4 || hero_turn_count_ == 7){
        return "mage";
    }
    else if(hero_turn_count_ == 2 || hero_turn_count_ == 5 || hero_turn_count_ == 8){
        return "knight";
    }
    else return "turno_indefinido";
    
}

void GameState::monsterTurn() {
}
