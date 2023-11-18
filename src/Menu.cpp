#include "Menu.h"
#include "Game.h"

void Menu::initMenuWindow() {
  this->menu_window_ = new sf::RenderWindow(sf::VideoMode(1200, 800), "Menu", sf::Style::Close);
  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
  int centro_x = (desktop.width - 1200) / 2;
  int centro_y = (desktop.height - 800) / 2;
  this->menu_window_->setPosition(sf::Vector2i(centro_x, centro_y));
}

Menu::Menu() {
  //Construindo background do menu
  menu_image_.loadFromFile("Textures/BackgroundMenu.png");
  menu_background_.setTexture(menu_image_);
  menu_background_.setScale(10, 9);

  //Construindo textos das opções do menu
  menu_font_.loadFromFile("Resources/Retro Gaming.ttf");
  menu_texts_.resize(4);
  printed_texts_ = {"Trinity", "Dungeon", "Jogar", "Sair"};
  texts_position_ = {{160, 20}, {260, 180}, {497, 418}, {534, 583}};
  texts_size_ = {140, 140, 60, 60};
  texts_color_ = {sf::Color::White, sf::Color::White, sf::Color(153, 51, 153), sf::Color::White};
  for (unsigned int i = 0; i < menu_texts_.size(); i++) {
    menu_texts_[i].setFont(menu_font_);
    menu_texts_[i].setString(printed_texts_[i]);
    menu_texts_[i].setCharacterSize(texts_size_[i]);
    menu_texts_[i].setFillColor(texts_color_[i]);
    menu_texts_[i].setPosition(texts_position_[i]);
  }

  //Inicializando variáveis
  position_ = 2;
  keyboard_pressed_ = enter_pressed_ = false;
  clock_ = sf::Clock();

  this->initMenuWindow();
  this->menu_close_ = new sf::RectangleShape();
}

Menu::~Menu() {
  delete menu_window_;
  delete menu_close_;
}

void Menu::loopEvents() {
  sf::Event event;
  while (menu_window_->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      menu_window_->close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !keyboard_pressed_) {
      if (position_ < 3) {
        position_++;
        keyboard_pressed_ = true;
        menu_texts_[position_].setFillColor(sf::Color(128, 128, 128));
        menu_texts_[position_-1].setFillColor(sf::Color::White);
      }
      keyboard_pressed_ = false;
      enter_pressed_ = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !keyboard_pressed_) {
      if (position_ > 2) {
        position_--;
        keyboard_pressed_ = true;
        menu_texts_[position_].setFillColor(sf::Color(153, 51, 153));
        menu_texts_[position_+1].setFillColor(sf::Color::White);
      }
      keyboard_pressed_ = false;
      enter_pressed_ = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !enter_pressed_) {
      enter_pressed_ = true;
      float open_time = clock_.getElapsedTime().asMilliseconds();

      if (position_ == 2 && open_time > 50) {
        sf::Clock clock;
        Game game;
        game.run(clock);
        menu_window_->close();
      }

      if (position_ == 3) {
        menu_window_->close();
      }
    }
  }
}

void Menu::drawMenu() {
  menu_window_->clear();
  menu_window_->draw(menu_background_);
  for (auto it : menu_texts_) {
    this->menu_window_->draw(it);
  }
  menu_window_->display();
}

void Menu::runMenu() {
  while(menu_window_->isOpen()) {
    drawMenu();
    loopEvents();
  }
}