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

class Game{
private:
    //Variables
    sf::RenderWindow *GameWindow;
    sf::Event SFML_event;
    Board *gameBoard;

    /// @brief Cria um novo objeto do tipo RenderWindow
    void initWindow();

    Hero mage;
    Hero knight;
    Hero rogue;


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
    void render(sf::Time delta_time);

    /// @brief Essa função garante que enquanto o jogo estiver aberto ele continue
    /// funcionando como deveria
    void run(sf::Clock clock);

    void boardRender(sf::Time delta_time);

};

#endif