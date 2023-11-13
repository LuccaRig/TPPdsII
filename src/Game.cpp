#include "Game.h"
#include "Hero.h"

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

void Game::initWindow(){
    this->GameWindow = new sf::RenderWindow(sf::VideoMode(1200, 800), "My Game");
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

void Game::boardRender(){
    Hero mage("mage");
    Hero knight("knight");

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            Tile* currentTile = this->gameBoard->getTileAt(i, j);

            //Transformar o tamanho do tabuleiro em pixels
            int board_width_pixels = currentTile->getTileSize() * 5;
            int board_height_pixels = currentTile->getTileSize() * 5;

            //Calcula as coordenadas para posicionar o tabuleiro no centro da janela
            int board_positionX = (this->GameWindow->getSize().x - board_width_pixels) / 2;
            int board_positionY = (this->GameWindow->getSize().y - board_height_pixels) / 2;

            sf::RectangleShape tileShape(sf::Vector2f(currentTile->getTileSize(), currentTile->getTileSize()));
            tileShape.setPosition(board_positionX + i * currentTile->getTileSize(), 
                                  board_positionY + j * currentTile->getTileSize());

            //Define a cor do quadrado como preto
            tileShape.setFillColor(sf::Color::Black);

            //Define a cor da borda como branca
            tileShape.setOutlineThickness(currentTile->getTileBorderSize());
            tileShape.setOutlineColor(sf::Color::White);

            //Desenha o quadrado na janela
            this->GameWindow->draw(tileShape);

            /// TODO: Modificar os valores i e j dos quadrados para as posições específicas dos herois
            if (i == 2 && j == 2) {
                // Cria o herói e configura sua posição para o centro do quadrado
                mage.getHeroSprite().setPosition(tileShape.getPosition().x + (tileShape.getSize().x - mage.getHeroSprite().getLocalBounds().width) / 2,
                                              tileShape.getPosition().y + (tileShape.getSize().y - mage.getHeroSprite().getLocalBounds().height) / 2);
                this->GameWindow->draw(mage.getHeroSprite());
            }
            if (i == 2 && j == 1) {
                // Cria o herói e configura sua posição para o centro do quadrado
                knight.getHeroSprite().setPosition(tileShape.getPosition().x + (tileShape.getSize().x - knight.getHeroSprite().getLocalBounds().width) / 2,
                                                tileShape.getPosition().y + (tileShape.getSize().y - knight.getHeroSprite().getLocalBounds().height) / 2);
                // Desenha o herói na janela
                this->GameWindow->draw(knight.getHeroSprite());
            }
        }
    }
}

void Game::render(sf::Time delta_time){
    this->GameWindow->clear();
    this->boardRender();
    this->GameWindow->display();  
}

void Game::run(sf::Clock clock){
    while(this->GameWindow->isOpen()){
        //Conta a passagem de tempo desde a ultima vez que o clock.restart() foi chamado
        sf::Time delta_time = clock.restart();
        this->update();
        this->render(delta_time);
    }

}
