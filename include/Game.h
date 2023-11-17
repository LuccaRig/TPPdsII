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
#include "Hordes.h"

class Game {

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

    void putHeroInBoard(int position_y, int position_x, Hero &hero, float delta_time,sf::RectangleShape &tileShape);

    void putMonsterInBoard(int position_y, int position_x, Monster &monster, float delta_time,sf::RectangleShape &tileShape);

    /// @brief Escreva os nomes dos heróis acimas de suas barras de vida
    void putHeroNames();

    /// @brief Coloca as barras de vida dos heróis na tela
    void putHeroHealthBars();

    /// @brief Muda o tamanho das barras de vida dos heróis
    /// TODO: Implementar essa função quando os ataques já estiverem funcionando
    void setHeroHealthBars();

    /// @brief Renderiza o tabuleiro com os personagens nele
    /// @param delta_time = tempo decorrido desde o ultimo clock/renderização
    void boardRender(float delta_time);

    /// @brief Garante o cotrole dos herois pelo jogador durante seu turno
    /// @param delta_time: Tempo decorrido desde o ultimo clock 
    /// @param clock: Um argumento do tipo sf::Clock para atualizar o delta time 
    void playerTurnControl(float delta_time, sf::Clock clock);

    /// @brief Movimenta os herois no tabuleiro
    /// @param hero: Heroi selecionado para andar no seu devido turno
    /// @param delta_time: Tempo decorrido desde o ultimo clock 
    /// @param clock: Um argumento do tipo sf::Clock para atualizar o delta time 
    void heroWalk(Hero &hero, float delta_time, sf::Clock clock);

  private:
    //Variables
    sf::RenderWindow *game_window_;
    sf::Event SFML_event_;
    sf::Texture background_;
    sf::Sprite background_sprite_;
    sf::Font font_;
    Board *game_board_;
    GameState *current_game_state_;

    //Personagens dos jogadores:
    Hero mage_;
    Hero knight_;
    Hero rogue_;
    Hordes my_hordes_;

    /// @brief Cria um novo objeto do tipo RenderWindow
    void initWindow();
};

#endif // GAME_H_