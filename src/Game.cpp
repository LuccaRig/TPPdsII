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
    this->GameWindow->draw(background_sprite_);
    this->boardRender(delta_time);
    this->GameWindow->display();  
}

void Game::PlayerTurnControl(float delta_time, sf::Clock clock){
        while(this->current_game_state_->IsPlayerTurn()){
            if(this->current_game_state_->WhichHeroTurn() == "knight"){
                
                this->update();
                this->render(delta_time);

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                    int pos = knight_.get_hero_position_y();
                    knight_.set_hero_position_y(pos-1);
                    this->current_game_state_->HeroTurnPass();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                    int pos = knight_.get_hero_position_y();
                    knight_.set_hero_position_y(pos+1);
                    this->current_game_state_->HeroTurnPass();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                    int pos = knight_.get_hero_position_x();
                    knight_.set_hero_position_x(pos-1);
                    this->current_game_state_->HeroTurnPass();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                    int pos = knight_.get_hero_position_x();
                    knight_.set_hero_position_x(pos+1);
                    this->current_game_state_->HeroTurnPass();
                }
            
            }

            else if(this->current_game_state_->WhichHeroTurn() == "mage"){
                
                this->update();
                this->render(delta_time);
                
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                    int pos = mage_.get_hero_position_y();
                    mage_.set_hero_position_y(pos-1);
                    this->current_game_state_->HeroTurnPass();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                    int pos = mage_.get_hero_position_y();
                    mage_.set_hero_position_y(pos+1);
                    this->current_game_state_->HeroTurnPass();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                    int pos = mage_.get_hero_position_x();
                    mage_.set_hero_position_x(pos-1);
                    this->current_game_state_->HeroTurnPass();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                    int pos = mage_.get_hero_position_x();
                    mage_.set_hero_position_x(pos+1);
                    this->current_game_state_->HeroTurnPass();
                }
        }

        else if(this->current_game_state_->WhichHeroTurn() == "rogue"){
                while(true){
                this->update();
                this->render(delta_time);
                
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                    int pos = rogue_.get_hero_position_y();
                    rogue_.set_hero_position_y(pos-1);
                    break;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                    int pos = rogue_.get_hero_position_y();
                    rogue_.set_hero_position_y(pos+1);
                    break;
                    //this->current_game_state_->HeroTurnPass();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                    int pos = rogue_.get_hero_position_x();
                    rogue_.set_hero_position_x(pos-1);
                    break;
                    //this->current_game_state_->HeroTurnPass();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                    int pos = rogue_.get_hero_position_x();
                    rogue_.set_hero_position_x(pos+1);
                    break;
                    //this->current_game_state_->HeroTurnPass();
                }
            }
            this->update();
            this->render(delta_time);

            this->current_game_state_->HeroTurnPass(); 
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

        //O PlayerTurnControl garante a movimentação e ataques dos herois
        this->PlayerTurnControl(delta_time, clock);   
    }

}
