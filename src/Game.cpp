#include "Game.h"

void Game::initWindow(){
    this->GameWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "My Game");

}

Game::Game(){
    this->initWindow();
}

Game::~Game(){
    delete this->GameWindow;
}


    //Methods
void Game::updateSFMLEvents(){
    while(this->GameWindow->pollEvent(this->SFML_event)){
        if(this->SFML_event.type == sf::Event::Closed){
            this->GameWindow->close();
        }
    }

}

void Game::update(){
    this->updateSFMLEvents();
}

void Game::render(){
    this->GameWindow->clear();

    this->GameWindow->display();
    
}

void Game::run(){
    while(this->GameWindow->isOpen()){
        this->update();
        this->render();
    }

}
