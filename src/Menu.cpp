#include "Menu.h"

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

  this->initMenuWindow();
  this->menu_close_ = new sf::RectangleShape();
}

Menu::~Menu() {
  delete menu_window_;
  delete menu_close_;
}

void Menu::set_values() {
  position_ = 0;
  keyboard_pressed = enter_pressed_ = false;
}

void Menu::loopEvents() {
  sf::Event event;
  while (menu_window_->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      menu_window_->close();
    }
  }
}

void Menu::drawMenu() {
  menu_window_->clear();
  menu_window_->draw(menu_background_);
  menu_window_->display();
}

void Menu::runMenu() {
  while(menu_window_->isOpen()) {
    loopEvents();
    drawMenu();
  }
}