#include "HeroMenu.h"

HeroMenu::HeroMenu() {
  //Construindo retângulo do menu dos heróis
  background_hero_menu_.setSize(sf::Vector2f(1100, 100));
  background_hero_menu_.setFillColor(sf::Color(70, 46, 64));
  background_hero_menu_.setPosition(sf::Vector2f(50, 600));

  //Construindo textos das opções do menu dos heróis
  hero_menu_font_.loadFromFile("Resources/Retro Gaming.ttf");
  hero_menu_texts_.resize(4);
  hero_menu_printed_texts_ = {"Mover", "Atacar", "Habilidade", "Esperar"};
  hero_menu_texts_position_ = {{70, 625}, {280, 625}, {516, 625}, {860, 625}};
  hero_menu_texts_color_ = {sf::Color::Green, sf::Color(64, 64, 64), sf::Color(64, 64, 64), sf::Color(64, 64, 64)};
  for (unsigned int i = 0; i < hero_menu_texts_.size(); i++) {
    hero_menu_texts_[i].setFont(hero_menu_font_);
    hero_menu_texts_[i].setString(hero_menu_printed_texts_[i]);
    hero_menu_texts_[i].setCharacterSize(50);
    hero_menu_texts_[i].setFillColor(hero_menu_texts_color_[i]);
    hero_menu_texts_[i].setPosition(hero_menu_texts_position_[i]);
  }

  //Inicializando variáveis
  hero_menu_position_ = 0;
  keyboard_pressed_hero_menu_ = enter_pressed_hero_menu_ = false;
  selected_choice_ = " ";
}

HeroMenu::~HeroMenu() {
}

void HeroMenu::loopChoicesEvents(sf::RenderWindow *game_window) {
sf::Event event;
while (game_window->pollEvent(event)) {
  if (event.type == sf::Event::Closed) {
    game_window->close();
  }
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Right && !keyboard_pressed_hero_menu_) {
      if (hero_menu_position_ < 3) {
        hero_menu_position_++;
        keyboard_pressed_hero_menu_ = true;
        if (hero_menu_position_ == 1) hero_menu_texts_[hero_menu_position_].setFillColor(sf::Color::Red);
        if (hero_menu_position_ == 2) hero_menu_texts_[hero_menu_position_].setFillColor(sf::Color::Blue);
        if (hero_menu_position_ == 3) hero_menu_texts_[hero_menu_position_].setFillColor(sf::Color::Black);
        hero_menu_texts_[hero_menu_position_-1].setFillColor(sf::Color(64, 64, 64));
      }
      keyboard_pressed_hero_menu_ = false;
      enter_pressed_hero_menu_ = false;
    }

    if (event.key.code == sf::Keyboard::Left && !keyboard_pressed_hero_menu_) {
      if (hero_menu_position_ > 0) {
        hero_menu_position_--;
        keyboard_pressed_hero_menu_ = true;
        if (hero_menu_position_ == 0) hero_menu_texts_[hero_menu_position_].setFillColor(sf::Color::Green);
        if (hero_menu_position_ == 1) hero_menu_texts_[hero_menu_position_].setFillColor(sf::Color::Red);
        if (hero_menu_position_ == 2) hero_menu_texts_[hero_menu_position_].setFillColor(sf::Color::Blue);
        hero_menu_texts_[hero_menu_position_+1].setFillColor(sf::Color(64, 64, 64));
      }
      keyboard_pressed_hero_menu_ = false;
      enter_pressed_hero_menu_ = false;
    }

    if (event.key.code == sf::Keyboard::Enter && !enter_pressed_hero_menu_) {
      enter_pressed_hero_menu_ = true;

      if (hero_menu_position_ == 0) {
        selected_choice_ = "move";
      } 

      if (hero_menu_position_ == 1) {
        selected_choice_ = "attack";
      }

      if (hero_menu_position_ == 2) {
        selected_choice_ = "skill";
      }

      if (hero_menu_position_ == 3) {
        selected_choice_ = "wait";
      }
    }
  }
}
}

void HeroMenu::drawHeroMenu(sf::RenderWindow *game_window) {
  game_window->draw(background_hero_menu_);
  for (auto it : hero_menu_texts_) {
    game_window->draw(it);
  }
}

std::string HeroMenu::get_selected_choice() {
  return selected_choice_;
}