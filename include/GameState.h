#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Board.h"
#include "Hero.h"
#include "Monster.h"


class GameState{
  public:

    /// @brief Constroi o objeto que controla o estado atual do jogo
    GameState();

    /// @brief Destructor/Desalocar a memoria dos vetores de alocação dinâmica
    ~GameState();

    /// @brief Inicializa o jogo e coloca os herois no tabuleiro;
    void GameStart();

    void HeroTurnPass();

    bool IsPlayerTurn();

    /// @brief Serve para o jogo controlar a passagem de turnos dos herois
    /// @return Uma string dizendo o turno de qual heroi está ocorrendo no presente momento 
    std::string WhichHeroTurn();

    void MonsterTurn();

  private:
    int hero_turn_count_;
    ///TODO:Verificar a alocação dinâmica do turno dos monstros
    int monster_turn_count_;
};




#endif // GAMESTATE_H_