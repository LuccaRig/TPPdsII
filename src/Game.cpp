#include "Game.h"

void Game::initWindow(){
    this->GameWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "My Game");
    this->gameBoard = new Board();
}

Game::Game(){
    this->initWindow();
}

Game::~Game(){
    delete this->GameWindow;
    delete this->gameBoard;
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

    //Renderização do tabuleiro:

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            Tile* currentTile = this->gameBoard->getTileAt(i, j);

            sf::RectangleShape tileShape(sf::Vector2f(currentTile->getTileSize(), currentTile->getTileSize()));
            tileShape.setPosition(i * currentTile->getTileSize(), j * currentTile->getTileSize());

            //Define a cor do quadrado como preto
            tileShape.setFillColor(sf::Color::Black);

            //Define a cor da borda como branca
            tileShape.setOutlineThickness(currentTile->getTileBorderSize());
            tileShape.setOutlineColor(sf::Color::White);

            //Desenha o quadrado na janela
            this->GameWindow->draw(tileShape);
        }
    }


    this->GameWindow->display();
    
}

void Game::run(){
    while(this->GameWindow->isOpen()){
        this->update();
        this->render();
    }

}
