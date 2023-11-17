#include "Game.h"
#include "Hero.h"
#include "GameState.h"

#include <iostream>
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

void Game::initWindow(){
    this->game_window_ = new sf::RenderWindow(sf::VideoMode(1200, 800), "My Game", sf::Style::Close);
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    int centro_x = (desktop.width - 1200) / 2;
    int centro_y = (desktop.height - 800) / 2;
    this->game_window_->setPosition(sf::Vector2i(centro_x, centro_y));
    this->game_board_ = new Board();
}

Game::Game() : mage_("mage"), knight_("knight"), rogue_("rogue"){
    //Construindo background
    background_.loadFromFile("Textures/Background.png");
    background_sprite_.setTexture(background_);
    background_sprite_.setScale(10, 10);

    //Construindo os nomes dos heróis e suas características
    font_.loadFromFile("Resources/Retro Gaming.ttf");
    heros_.resize(3);
    hero_names_ = {"Knight", "Mage", "Rogue"};
    hero_names_position_ = {{20, 20}, {20, 140}, {20, 260}};
    for (unsigned int i = 0; i < heros_.size(); i++) {
        heros_[i].setFont(font_);
        heros_[i].setString(hero_names_[i]);
        heros_[i].setCharacterSize(30);
        heros_[i].setFillColor(sf::Color::White);
        heros_[i].setPosition(hero_names_position_[i]);
    }

    //Construindo as barras de vida dos heróis e suas características
    health_bars_.resize(3);
    health_bars_position_ = {{20, 70}, {20, 190}, {20, 310}};
    for (unsigned int i = 0; i < health_bars_.size(); i++) {
        health_bars_[i].setSize(sf::Vector2f(190, 30));
        health_bars_[i].setFillColor(sf::Color(128, 0, 0));
        health_bars_[i].setPosition(health_bars_position_[i]);
    }

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
    for (auto it : heros_) {
        this->game_window_->draw(it);
    }
    for (auto it : health_bars_) {
        this->game_window_->draw(it);
    }
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


void Game::monsterTakeAction(std::vector<Monster> &monster, int number_of_monsters, float delta_time, sf::Clock clock) {
    struct heroes {
        int pos_x;
        int pos_y;
        double distance;
        int distance_x;
        int distance_y;
    };
    heroes hero[3];

    // armazena as coordenadas dos heróis no board
    int current_hero = 0;
        for (int i = 0; i < 5 && current_hero < 3; i++) {
            for (int j = 0; j < 5; j++) {
                if (game_board_->get_tile_at(i, j)->heroIsInTile()) {
                    hero[current_hero].pos_x = i;
                    hero[current_hero].pos_y = j;
                    current_hero++;
                }
            }   
        }

    for(int n = 0; n < number_of_monsters; n++) {
        int monster_pos_x = monster[n].get_monster_position_x();
        int monster_pos_y = monster[n].get_monster_position_y();
        heroes nearest_hero = hero[0];

        // descobre e armazena qual o herói mais próximo ao monstro 
        for (int m = 0; m < 3; m++) {
            hero[m].distance_x = monster_pos_x - hero[m].pos_x;
            hero[m].distance_y = monster_pos_y - hero[m].pos_y;
            hero[m].distance = std::sqrt(std::pow(hero[m].distance_x, 2) + 
            std::pow(hero[m].distance_y, 2));
            if (hero[m].distance < nearest_hero.distance) nearest_hero = hero[m];
        }

        // decide qual será a ação do monstro sabendo qual o herói mais próximo a ele

       // if (nearest_hero.distance == 1) monster[n].attackHero(game_board_->get_tile_at
       // (nearest_hero.pos_x, nearest_hero.pos_y)->)

        // tem que virar else if quando o if acima funcionar
        if (fabs(nearest_hero.distance_x) >= fabs(nearest_hero.distance_y)) { 
            if (nearest_hero.distance_x > 0) {
                monster[n].set_monster_position_x(monster_pos_x-1);
                game_board_->get_tile_at(monster_pos_x, monster_pos_y)->deleteObjectInTile();
                game_board_->get_tile_at((monster_pos_x-1), monster_pos_y)->setObjectInTile("monster");
            } 
            else if (nearest_hero.distance_x < 0) {
                monster[n].set_monster_position_x(monster_pos_x+1);
                game_board_->get_tile_at(monster_pos_x, monster_pos_y)->deleteObjectInTile();
                game_board_->get_tile_at((monster_pos_x+1), monster_pos_y)->setObjectInTile("monster");

            }
        }

        else if (fabs(nearest_hero.distance_x) < fabs(nearest_hero.distance_y)){
            if (nearest_hero.distance_y > 0) {
                monster[n].set_monster_position_y(monster_pos_y-1);
                game_board_->get_tile_at(monster_pos_x, monster_pos_y)->deleteObjectInTile();
                game_board_->get_tile_at(monster_pos_x, (monster_pos_y-1))->setObjectInTile("monster");
            } else if (nearest_hero.distance_y < 0) {
                monster[n].set_monster_position_y(monster_pos_y+1);
                game_board_->get_tile_at(monster_pos_x, monster_pos_y)->deleteObjectInTile();
                game_board_->get_tile_at(monster_pos_x, (monster_pos_y+1))->setObjectInTile("monster");
            }
        }

        else {

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
