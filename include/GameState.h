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
#include "Enemies.h"


class GameState{
  public:

    /// @brief Constroi o objeto que controla o estado atual do jogo
    GameState();

    /// @brief Destructor/Desalocar a memoria dos vetores de alocação dinâmica
    ~GameState();

    /// @brief Aumenta o contador dos turnos dos herois
    void heroTurnPass();

    /// @brief zera o contador dos turnos dos heróis
    void heroTurnRestart();

    /// @brief Enquanto o contador de turnos dos herois for menor que um valor definido
    /// essa função retorna true 
    bool isPlayerTurn(int hero_greatest_turn);

    bool isGameOver(Hero &rogue, Hero &mage, Hero &knight);

    bool playerVictory(Enemies &my_horde);

    /// @brief Serve para o jogo controlar a passagem de turnos dos herois
    /// @return Uma string dizendo o turno de qual heroi está ocorrendo no presente momento 
    std::string whichHeroTurn(Hero &rogue, Hero &mage, Hero &knight);

  private:
    int hero_turn_count_;
    int monster_turn_count_;
};

#endif // GAMESTATE_H_