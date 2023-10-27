#include "Game.h"

void Game::initWindow(){
    this->GameWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "My Game");
    this->GameWindow->setPosition(sf::Vector2i(0,0));

    background_.loadFromFile("Resources/SpritesTobeUsed.png");
    this->background_pointer = new sf::Sprite;
    
    this->background_pointer->setTexture(background_);

}

Game::Game(){
    this->initWindow();
}

Game::~Game(){
    delete this->GameWindow;
}


    //Methods

void Game::testIsClosed(){
    while(this->GameWindow->pollEvent(this->SFML_event)){
        if(this->SFML_event.type == sf::Event::Closed){
            this->GameWindow->close();
        }
    }

}

void Game::update(){
    this->testIsClosed();

}

void Game::render(){
    this->GameWindow->clear();
    this->GameWindow->draw(*(this->background_pointer));
    this->GameWindow->display();
    
}

void Game::run(){
    while(this->GameWindow->isOpen()){
        this->update();
        this->render();
    }

}
