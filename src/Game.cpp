#include "Game.h"
#include "Hero.h"

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

void Game::initWindow(){
    this->GameWindow = new sf::RenderWindow(sf::VideoMode(1200, 800), "My Game",sf::Style::Close);
    this->gameBoard = new Board();
}

Game::Game() : mage_("mage"), knight_("knight"), rogue_("rogue"){
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

void Game::boardRender(float delta_time){
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
            if (i == mage_.get_hero_position_x() && j == mage_.get_hero_position_y()) {
                // Cria o herói e configura sua posição para o centro do quadrado
                mage_.getHeroSprite().setScale(3.f, 3.f);
                mage_.getHeroSprite().setPosition(tileShape.getPosition().x + (tileShape.getSize().x - mage_.getHeroSprite().getLocalBounds().width*3) / 2,
                                              tileShape.getPosition().y + (tileShape.getSize().y - mage_.getHeroSprite().getLocalBounds().height*3) / 2);

                mage_.updateAnimation(delta_time);
                // Desenha o herói na janela
                this->GameWindow->draw(mage_.getHeroSprite());
            }
            if (i == knight_.get_hero_position_x() && j == knight_.get_hero_position_y()) {
                // Cria o herói e configura sua posição para o centro do quadrado
                knight_.getHeroSprite().setScale(3.f, 3.f);
                knight_.getHeroSprite().setPosition(tileShape.getPosition().x + (tileShape.getSize().x - knight_.getHeroSprite().getLocalBounds().width*3) / 2,
                                                tileShape.getPosition().y + (tileShape.getSize().y - knight_.getHeroSprite().getLocalBounds().height*3) / 2);
                knight_.updateAnimation(delta_time);
                // Desenha o herói na janela
                this->GameWindow->draw(knight_.getHeroSprite());
            }
            if (i == rogue_.get_hero_position_x() && j == rogue_.get_hero_position_y()) {
                // Cria o herói e configura sua posição para o centro do quadrado
                rogue_.getHeroSprite().setScale(3.f, 3.f);
                rogue_.getHeroSprite().setPosition(tileShape.getPosition().x + (tileShape.getSize().x - rogue_.getHeroSprite().getLocalBounds().width*3) / 2,
                                                tileShape.getPosition().y + (tileShape.getSize().y - rogue_.getHeroSprite().getLocalBounds().height*3) / 2);
                rogue_.updateAnimation(delta_time);
                // Desenha o herói na janela
                this->GameWindow->draw(rogue_.getHeroSprite());
            }
        }
    }
}

void Game::render(float delta_time){
    this->GameWindow->clear();
    this->boardRender(delta_time);
    this->GameWindow->display();  
}

void Game::run(sf::Clock clock){
    while(this->GameWindow->isOpen()){
        //Conta a passagem de tempo desde a ultima vez que o clock.restart() foi chamado
        float delta_time = clock.restart().asSeconds();
        this->update();
        this->render(delta_time);
    }

}
