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
    this->game_window_ = new sf::RenderWindow(sf::VideoMode(1200, 800), "My Game",sf::Style::Close);
    this->game_window_->setPosition(sf::Vector2i(0, 0));
    this->game_board_ = new Board();
}

Game::Game() : mage_("mage"), knight_("knight"), rogue_("rogue"){
    background_.loadFromFile("Textures/Background.png");
    background_sprite_.setTexture(background_);
    background_sprite_.setScale(10, 10);
    this->initWindow();
    this->current_game_state_ = new GameState();
}

Game::~Game(){
    delete this->game_window_;
    delete this->game_board_;
    delete this->current_game_state_;
}


    //Methods

void Game::testIsClosed() {
    while(this->game_window_->pollEvent(this->SFML_event_)){
        if(this->SFML_event_.type == sf::Event::Closed){
            this->game_window_->close();
        }
    }

}

void Game::update() {
    this->testIsClosed();
}

void Game::putHeroInBoard(int position_x, int position_y, Hero &hero, float delta_time, sf::RectangleShape &tileShape) {
    if (position_x == hero.get_hero_position_x() && position_y == hero.get_hero_position_y()) {
    //Modifica o tamanho do sprite do heroi para ficar um tamanho proporcional ao tabuleiro
    game_board_->get_tile_at(position_x, position_y)->setObjectInTile("hero");
    hero.get_hero_sprite().setScale(3.f, 3.f);
    hero.get_hero_sprite().setPosition(tileShape.getPosition().x + (tileShape.getSize().x - hero.get_hero_sprite().getLocalBounds().width*3) / 2,
                                              tileShape.getPosition().y + (tileShape.getSize().y - hero.get_hero_sprite().getLocalBounds().height*3) / 2);
    hero.updateAnimation(delta_time);
    
    // Desenha o herói na janela
    this->game_window_->draw(hero.get_hero_sprite());
    }
}

void Game::putMonsterInBoard(int position_x, int position_y, Monster &monster, float delta_time, sf::RectangleShape &tileShape) {
    if (position_x == monster.get_monster_position_x() && position_y == monster.get_monster_position_y()) {
    //Modifica o tamanho do sprite do monstro para ficar um tamanho proporcional ao tabuleiro
    game_board_->get_tile_at(position_x, position_y)->setObjectInTile("monster");
    monster.get_monster_sprite().setScale(3.f, 3.f);
    monster.get_monster_sprite().setPosition(tileShape.getPosition().x + (tileShape.getSize().x - monster.get_monster_sprite().getLocalBounds().width*3) / 2,
                                              tileShape.getPosition().y + (tileShape.getSize().y - monster.get_monster_sprite().getLocalBounds().height*3) / 2);
    monster.updateAnimation(delta_time);
    
    // Desenha o monstro na janela
    this->game_window_->draw(monster.get_monster_sprite());
    }
}

void Game::boardRender(float delta_time) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            Tile* currentTile = this->game_board_->get_tile_at(i, j);

            //Transformar o tamanho do tabuleiro em pixels
            int board_width_pixels = currentTile->getTileSize() * 5;
            int board_height_pixels = currentTile->getTileSize() * 5;

            //Calcula as coordenadas para posicionar o tabuleiro junto ao background
            int board_positionX = (this->game_window_->getSize().x - board_width_pixels) / 1.98;
            int board_positionY = (this->game_window_->getSize().y - board_height_pixels) / 6;

            sf::RectangleShape tileShape(sf::Vector2f(currentTile->getTileSize(), currentTile->getTileSize()));
            tileShape.setPosition(board_positionX + i * currentTile->getTileSize(), 
                                  board_positionY + j * currentTile->getTileSize());
            //Define a cor do quadrado como transparente
            tileShape.setFillColor(sf::Color::Transparent);
            //Desenha o quadrado na janela
            this->game_window_->draw(tileShape);

            putHeroInBoard(i, j, mage_, delta_time, tileShape);
            putHeroInBoard(i, j, knight_, delta_time, tileShape);
            putHeroInBoard(i, j, rogue_, delta_time, tileShape);        
        }
    }
}

void Game::render(float delta_time) {
    this->game_window_->clear();
    this->game_window_->draw(background_sprite_);
    this->boardRender(delta_time);
    this->game_window_->display();  
}

void Game::heroWalk(Hero &hero, float delta_time, sf::Clock clock) {
    while(this->game_window_->pollEvent(this->SFML_event_)){
        int pos_x = 0, pos_y = 0;
        this->update();
        this->render(delta_time);
        delta_time = clock.restart().asSeconds();

        if(this->SFML_event_.type == sf::Event::KeyPressed){ 
            switch (this->SFML_event_.key.code) {
                case sf::Keyboard::Up:
                    pos_y = hero.get_hero_position_y();
                    pos_x = hero.get_hero_position_x();
                    if ((pos_y-1) < 0 || !game_board_->get_tile_at(pos_x, (pos_y-1))->moveableTile()) continue;
                    hero.set_hero_position_y(pos_y-1);
                    game_board_->get_tile_at(pos_x, pos_y)->deleteObjectInTile();
                    game_board_->get_tile_at(pos_x, (pos_y-1))->setObjectInTile("hero");
                    this->current_game_state_->heroTurnPass();
                    break;

                case sf::Keyboard::Down:
                    pos_y = hero.get_hero_position_y();
                    pos_x = hero.get_hero_position_x();
                    if ((pos_y+1) > 4 || !game_board_->get_tile_at(pos_x, (pos_y+1))->moveableTile()) continue;
                    hero.set_hero_position_y(pos_y+1);
                    game_board_->get_tile_at(pos_x, pos_y)->deleteObjectInTile();
                    game_board_->get_tile_at(pos_x, (pos_y+1))->setObjectInTile("hero");
                    this->current_game_state_->heroTurnPass();
                    break;

                case sf::Keyboard::Left:
                    pos_x = hero.get_hero_position_x();
                    pos_y = hero.get_hero_position_y();
                    if ((pos_x-1) < 0 || !game_board_->get_tile_at((pos_x-1), pos_y)->moveableTile()) continue;
                    hero.set_hero_position_x(pos_x-1);
                    game_board_->get_tile_at(pos_x, pos_y)->deleteObjectInTile();
                    game_board_->get_tile_at((pos_x-1), pos_y)->setObjectInTile("hero");
                    this->current_game_state_->heroTurnPass();
                    break;

                case sf::Keyboard::Right:
                    pos_x = hero.get_hero_position_x();
                    pos_y = hero.get_hero_position_y();
                    if ((pos_x+1) > 4 || !game_board_->get_tile_at((pos_x+1), pos_y)->moveableTile()) continue;
                    hero.set_hero_position_x(pos_x+1);
                    game_board_->get_tile_at(pos_x, pos_y)->deleteObjectInTile();
                    game_board_->get_tile_at((pos_x+1), pos_y)->setObjectInTile("hero");
                    this->current_game_state_->heroTurnPass();
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


void Game::playerTurnControl(float delta_time, sf::Clock clock) {
    while(this->current_game_state_->isPlayerTurn()){
        this->update();
        this->render(delta_time);
        delta_time = clock.restart().asSeconds();

        if(current_game_state_->whichHeroTurn() == "rogue"){
            heroWalk(rogue_, delta_time, clock);
        }
        
        else if(current_game_state_->whichHeroTurn() == "mage"){
            heroWalk(mage_, delta_time, clock);
        }

        else if(current_game_state_->whichHeroTurn() == "knight"){
            heroWalk(knight_, delta_time, clock);
        }
    }
}

void Game::run(sf::Clock clock) {
    float delta_time = clock.restart().asSeconds();
    while(this->game_window_->isOpen()) {
        
        //Conta a passagem de tempo desde a ultima vez que o clock.restart() foi chamado
        delta_time = clock.restart().asSeconds();
        
        //Essa linha atualiza a tela enquanto o x não for apertado
        this->update();

        //Essa linha de código renderiza o tabuleiro e todas as imagens inclusas nela
        this->render(delta_time);

        //O playerTurnControl garante a movimentação e ataques dos herois durante o turno do jogador
        this->playerTurnControl(delta_time, clock);   
    }

}
