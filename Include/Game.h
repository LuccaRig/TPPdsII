#ifndef GAME_H
#define GAME_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game{
private:
    //Variables
    sf::RenderWindow *GameWindow;
    sf::Event SFML_event;

    //Inicialization
    void initWindow();


public:
    
    /// @brief Constructor
    Game();

    /// @brief Destructor
    virtual ~Game();

    //Methods

    void updateSFMLEvents();
    void update();
    void render();
    void run();

};

#endif