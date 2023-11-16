#include "GameState.h"

GameState::GameState(){
    horde_number_ = 0;
    monster_turn_count_ = 0;
}

GameState::~GameState()
{
}

void GameState::GameStart(){
}

void GameState::HeroTurnPass(){
    hero_turn_count_++;
}

bool GameState::IsPlayerTurn(){
    if(hero_turn_count_ < 9){
        return true;
    }
    else{
        return false;
    }
    
}

std::string GameState::WhichHeroTurn(){
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

void GameState::MonsterTurn()
{
}
