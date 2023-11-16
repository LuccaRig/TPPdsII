#include "Game.h"
#include "Hero.h"
#include "GameState.h"

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

void Game::initWindow(){
    this->GameWindow = new sf::RenderWindow(sf::VideoMode(1200, 800), "My Game",sf::Style::Close);
    this->GameWindow->setPosition(sf::Vector2i(0, 0));
    this->gameBoard = new Board();
}

Game::Game() : mage_("mage"), knight_("knight"), rogue_("rogue"){
    background_.loadFromFile("Textures/Background.png");
    background_sprite_.setTexture(background_);
    background_sprite_.setScale(10, 10);
    this->initWindow();
    this->current_game_state_ = new GameState();
}

Game::~Game(){
    delete this->GameWindow;
    delete this->gameBoard;
    delete this->current_game_state_;
}


    //Methods

void Game::testIsClosed(){
    while(this->GameWindow->pollEvent(this->SFML_event_)){
        if(this->SFML_event_.type == sf::Event::Closed){
            this->GameWindow->close();
        }
    }

}

void Game::update(){
    this->testIsClosed();
}

void Game::PutHeroInBoard(Hero &hero, float delta_time,sf::RectangleShape &tileShape){
    hero.getHeroSprite().setScale(3.f, 3.f);
    hero.getHeroSprite().setPosition(tileShape.getPosition().x + (tileShape.getSize().x - hero.getHeroSprite().getLocalBounds().width*3) / 2,
                                              tileShape.getPosition().y + (tileShape.getSize().y - hero.getHeroSprite().getLocalBounds().height*3) / 2);

    hero.updateAnimation(delta_time);
    // Desenha o herói na janela
    this->GameWindow->draw(hero.getHeroSprite());
}

void Game::boardRender(float delta_time){
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            Tile* currentTile = this->gameBoard->getTileAt(i, j);

            //Transformar o tamanho do tabuleiro em pixels
            int board_width_pixels = currentTile->getTileSize() * 5;
            int board_height_pixels = currentTile->getTileSize() * 5;

            //Calcula as coordenadas para posicionar o tabuleiro junto ao background
            int board_positionX = (this->GameWindow->getSize().x - board_width_pixels) / 1.98;
            int board_positionY = (this->GameWindow->getSize().y - board_height_pixels) / 6;

            sf::RectangleShape tileShape(sf::Vector2f(currentTile->getTileSize(), currentTile->getTileSize()));
            tileShape.setPosition(board_positionX + i * currentTile->getTileSize(), 
                                  board_positionY + j * currentTile->getTileSize());

            //Define a cor do quadrado como transparente
            tileShape.setFillColor(sf::Color::Transparent);

            //Desenha o quadrado na janela
            this->GameWindow->draw(tileShape);

            if (i == mage_.get_hero_position_x() && j == mage_.get_hero_position_y()) {
                PutHeroInBoard(mage_, delta_time, tileShape);
            }
            if (i == knight_.get_hero_position_x() && j == knight_.get_hero_position_y()) {
                
                PutHeroInBoard(knight_, delta_time, tileShape);
            }
            if (i == rogue_.get_hero_position_x() && j == rogue_.get_hero_position_y()) {
                PutHeroInBoard(rogue_, delta_time, tileShape);
            }
        }
    }
}

void Game::render(float delta_time){
    this->GameWindow->clear();
    this->GameWindow->draw(background_sprite_);
    this->boardRender(delta_time);
    this->GameWindow->display();  
}

void Game::HeroWalk(Hero &hero, float delta_time, sf::Clock clock){
    while(this->GameWindow->pollEvent(this->SFML_event_)){
        int pos = 0;
        this->update();
        this->render(delta_time);
        delta_time = clock.restart().asSeconds();

        if(this->SFML_event_.type == sf::Event::KeyPressed){ 
            switch (this->SFML_event_.key.code){
                case sf::Keyboard::Up:
                    pos = hero.get_hero_position_y();
                    hero.set_hero_position_y(pos-1);
                    this->current_game_state_->HeroTurnPass();
                    break;

                case sf::Keyboard::Down:
                    pos = hero.get_hero_position_y();
                    hero.set_hero_position_y(pos+1);
                    this->current_game_state_->HeroTurnPass();
                    break;

                case sf::Keyboard::Left:
                    pos = hero.get_hero_position_x();
                    hero.set_hero_position_x(pos-1);
                    this->current_game_state_->HeroTurnPass();
                    break;

                case sf::Keyboard::Right:
                    pos = hero.get_hero_position_x();
                    hero.set_hero_position_x(pos+1);
                    this->current_game_state_->HeroTurnPass();
                    break;

                default:
                    this->update();
                    this->render(delta_time);
                    delta_time = clock.restart().asSeconds();
                    break;

            }
        }
    }
}


void Game::PlayerTurnControl(float delta_time, sf::Clock clock){
    while(this->current_game_state_->IsPlayerTurn()){
        this->update();
        this->render(delta_time);
        delta_time = clock.restart().asSeconds();

        if(current_game_state_->WhichHeroTurn() == "rogue"){
            HeroWalk(rogue_, delta_time, clock);
        }
        
        else if(current_game_state_->WhichHeroTurn() == "mage"){
            HeroWalk(mage_, delta_time, clock);
        }

        else if(current_game_state_->WhichHeroTurn() == "knight"){
            HeroWalk(knight_,delta_time,clock);
        }
    }
}

void Game::run(sf::Clock clock){
    float delta_time = clock.restart().asSeconds();
    while(this->GameWindow->isOpen()){
        
        //Conta a passagem de tempo desde a ultima vez que o clock.restart() foi chamado
        delta_time = clock.restart().asSeconds();
        
        //Essa linha atualiza a tela enquanto o x não for apertado
        this->update();

        //Essa linha de código renderiza o tabuleiro e todas as imagens inclusas nela
        this->render(delta_time);

        //O PlayerTurnControl garante a movimentação e ataques dos herois durante o turno do jogador
        this->PlayerTurnControl(delta_time, clock);   
    }

}
