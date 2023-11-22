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

void GameState::heroTurnRestart() {
    hero_turn_count_ = 0;
} 

bool GameState::isPlayerTurn(int hero_greatest_turn) {
    if(hero_turn_count_ < hero_greatest_turn){
        return true;
    }
    else{
        return false;
    }
    
}

bool GameState::isGameOver(Hero &rogue, Hero &mage, Hero &knight) {
    if(rogue.isAlive() || mage.isAlive() || knight.isAlive()) return false;
    else return true;
}

std::string GameState::whichHeroTurn(Hero &rogue, Hero &mage, Hero &knight) {
  if (rogue.isAlive() && mage.isAlive() && knight.isAlive()) {
    if(hero_turn_count_ == 0){
        return "rogue";
    }
    else if(hero_turn_count_ == 1){
        return "mage";
    }
    else if(hero_turn_count_ == 2){
        return "knight";
    }
  }
  else if (!rogue.isAlive() && !mage.isAlive()) {
    return "knight";
  } 
  else if (!rogue.isAlive() && !knight.isAlive()) {
    return "mage";
  }
  else if (!mage.isAlive() && !knight.isAlive()) {
    return "rogue";
  }
  else if (!rogue.isAlive()) {
    if (hero_turn_count_ == 0) {
        return "mage";
    }
    else if (hero_turn_count_ == 1) {
        return "knight";
    }
  }
  else if (!mage.isAlive()) {
    if (hero_turn_count_ == 0) {
        return "rogue";
    }
    else if (hero_turn_count_ == 1) {
        return "knight";
    }
  }
  else if (!knight.isAlive()) {
    if (hero_turn_count_ == 0) {
        return "rogue";
    }
    else if (hero_turn_count_ == 1) {
        return "mage";
    }
  }
  else {
    return "turno_indefinido";
  }
}
