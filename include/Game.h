#ifndef GAME_H_
#define GAME_H_

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Board.h"
#include "Hero.h"
#include "GameState.h"

class Game{
private:
    //Variables
    sf::RenderWindow *GameWindow;
    sf::Event SFML_event_;
    sf::Texture background_;
    sf::Sprite background_sprite_;
    Board *gameBoard;
    GameState *current_game_state_;

    //Personagens dos jogadores:
    Hero mage_;
    Hero knight_;
    Hero rogue_;

    /// @brief Cria um novo objeto do tipo RenderWindow
    void initWindow();

public:
    
    /// @brief Constructor
    Game();

    /// @brief Destructor
    virtual ~Game();

    //Methods

    /// @brief Enquanto houver eventos ocorrendo na janela
    /// testa se um dos eventos é do tipo Closed(Apertar no x da janela)
    void testIsClosed();

    /// @brief Atualiza a janela para cada evento que deve ocorrer
    void update();

    /// @brief Limpa a tela que foi renderizada e em seguida renderiza novas imagens
    /// @param delta_time = tempo decorrido desde o ultimo clock/renderização
    void render(float delta_time);

    /// @brief Essa função garante que enquanto o jogo estiver aberto ele continue
    /// funcionando como deveria
    void run(sf::Clock clock);

    void PutHeroInBoard(int position_y, int position_x, Hero &hero, float delta_time,sf::RectangleShape &tileShape);

    void PutMonsterInBoard(int position_y, int position_x, Monster &monster, float delta_time,sf::RectangleShape &tileShape);

    /// @brief Renderiza o tabuleiro com os personagens nele
    /// @param delta_time = tempo decorrido desde o ultimo clock/renderização
    void boardRender(float delta_time);

    /// @brief Garante o cotrole dos herois pelo jogador durante seu turno
    /// @param delta_time: Tempo decorrido desde o ultimo clock 
    /// @param clock: Um argumento do tipo sf::Clock para atualizar o delta time 
    void PlayerTurnControl(float delta_time, sf::Clock clock);

    /// @brief Movimenta os herois no tabuleiro
    /// @param hero: Heroi selecionado para andar no seu devido turno
    /// @param delta_time: Tempo decorrido desde o ultimo clock 
    /// @param clock: Um argumento do tipo sf::Clock para atualizar o delta time 
    void HeroWalk(Hero &hero, float delta_time, sf::Clock clock);

};

#endif