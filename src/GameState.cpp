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

std::string GameState::HeroTurn()
{
    return "rogue";
}

void GameState::MonsterTurn()
{
}
