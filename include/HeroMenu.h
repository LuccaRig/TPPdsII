#ifndef HEROMENU_H_
#define HEROMENU_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class HeroMenu {

  public:

    HeroMenu();

    ~HeroMenu();

    void loopChoicesEvents(sf::RenderWindow *game_window);

    void drawHeroMenu(sf::RenderWindow *game_window);

    std::string get_selected_choice();

  private:

    int hero_menu_position_;
    bool keyboard_pressed_hero_menu_, enter_pressed_hero_menu_;
    std::string selected_choice_;

    sf::Font hero_menu_font_;

    sf::RectangleShape background_hero_menu_;

    std::vector<sf::Text> hero_menu_texts_;
    std::vector<std::string> hero_menu_printed_texts_;
    std::vector<sf::Vector2f> hero_menu_texts_position_;
    std::vector<sf::Color> hero_menu_texts_color_;
};

#endif // HEROMENU_H_