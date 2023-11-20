#include "GameState.h"

GameState::GameState(){
    hero_turn_count_ = 0;
    monster_turn_count_ = 0;
}

GameState::~GameState() {
}

void GameState::heroTurnPass() {
    hero_turn_count_++;
}

bool GameState::isPlayerTurn() {
    if(hero_turn_count_ < 15){
        return true;
    }
    else{
        return false;
    }
    
}

std::string GameState::whichHeroTurn(){
    if(hero_turn_count_%3 == 0){
        return "rogue";
    }
    else if(hero_turn_count_%3 == 1){
        return "mage";
    }
    else if(hero_turn_count_%3 == 2){
        return "knight";
    }
    else return "turno_indefinido";
    
}
