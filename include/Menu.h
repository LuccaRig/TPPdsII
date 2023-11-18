#ifndef MENU_H_
#define MENU_H_

#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Menu {

  public:

    Menu();

    ~Menu();

    void initMenuWindow();

    void loopEvents();

    void drawMenu();

    void runMenu();

  private:

    int position_;
    bool keyboard_pressed_, enter_pressed_;

    sf::RenderWindow *menu_window_;
    sf::RectangleShape *menu_close_;
    sf::Font menu_font_;
    sf::Texture menu_image_;
    sf::Sprite menu_background_;

    std::vector<sf::Text> menu_texts_;
    std::vector<std::string> printed_texts_;
    std::vector<sf::Vector2f> texts_position_;
    std::vector<int> texts_size_;
    std::vector<sf::Color> texts_color_;

};

#endif // MENU_H_