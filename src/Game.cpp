#include "Game.h"
#include "Hero.h"
#include "GameState.h"
#include "Enemies.h"

#include <iostream>
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

void Game::initWindow(){
    this->game_window_ = new sf::RenderWindow(sf::VideoMode(1200, 800), "Trinity Dungeon", sf::Style::Close);
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    int centro_x = (desktop.width - 1200) / 2;
    int centro_y = (desktop.height - 800) / 2;
    this->game_window_->setPosition(sf::Vector2i(centro_x, centro_y));
    this->game_board_ = new Board();
}

Game::Game() : mage_("mage"), knight_("knight"), rogue_("rogue") {
    //Construindo background
    background_.loadFromFile("Textures/Background.png");
    background_sprite_.setTexture(background_);
    background_sprite_.setScale(10, 10);

    //Construindo os nomes dos heróis e suas barras de vida
    herosNameInicialization();

    this->initWindow();
    this->current_game_state_ = new GameState();
}

Game::~Game(){
    delete this->game_window_;
    delete this->game_board_;
    delete this->current_game_state_;
}


    //Methods

void Game::herosNameInicialization() {
    font_.loadFromFile("Resources/Retro Gaming.ttf");
    heros_.resize(3);
    hero_names_ = {"Cavaleiro", "Mago", "Ladino"};
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
}

void Game::gameOverRender() {
    sf::RectangleShape rectangle(sf::Vector2f(490, 200));
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setOutlineColor(sf::Color::White);
    rectangle.setOutlineThickness(2); 

    rectangle.setPosition(360, 540);

    font_.loadFromFile("Resources/Retro Gaming.ttf");
    sf::Text game_over_text("Game Over", font_, 50);
    game_over_text.setFillColor(sf::Color::White);
    sf::Text press_esc_quit("press esc to quit", font_, 20);
    press_esc_quit.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = game_over_text.getLocalBounds();
    game_over_text.setPosition(rectangle.getPosition().x + (rectangle.getSize().x - textBounds.width) / 2,
                             rectangle.getPosition().y + (rectangle.getSize().y - textBounds.height) / 3);

    sf::FloatRect textBounds2 = press_esc_quit.getLocalBounds();
    press_esc_quit.setPosition(rectangle.getPosition().x + (rectangle.getSize().x - textBounds2.width) / 2,
                             rectangle.getPosition().y + (rectangle.getSize().y - textBounds2.height) / 1.3);

    this->game_window_->draw(rectangle);
    this->game_window_->draw(game_over_text); 
    this->game_window_->draw(press_esc_quit);
}

void Game::gameOverCloseWindow(float delta_time, sf::Clock clock) {
    while(this->current_game_state_->isGameOver(rogue_, mage_, knight_) && 
    this->game_window_->pollEvent(this->SFML_event_)) {
        this->render(delta_time);
        delta_time = clock.restart().asSeconds();
        if(this->SFML_event_.type == sf::Event::Closed || this->SFML_event_.type == sf::Event::KeyPressed){
            this->game_window_->close();
        }
    }
}

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
    if(!hero.isAlive()){
        game_board_->get_tile_at(position_x, position_y)->deleteObjectInTile();
        hero.set_hero_position_x(60);
        hero.set_hero_position_y(60);
        return;
    }
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

void Game::set_hero_health_bars(int hero, int full_hp, int current_hp) {
    health_bars_[hero].setSize(sf::Vector2f(190*current_hp/full_hp, 30));
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
            for(int k=0;k < my_hordes_.hordeSize();++k){
                putMonsterInBoard(i, j, *(my_hordes_.enemy(k)), delta_time, tileShape);
            }
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
    if (current_game_state_->isPlayerTurn(rogue_.isAlive() + mage_.isAlive() + knight_.isAlive()) && 
                !current_game_state_->isGameOver(rogue_, mage_, knight_)) {
        this->game_window_->draw(background_hero_menu_);
        for (auto it : hero_menu_texts_) {
            this->game_window_->draw(it);
        }
        this->game_window_->draw(which_hero_);
        this->game_window_->draw(which_direction_);
    };
    this->boardRender(delta_time);
    if(this->current_game_state_->isGameOver(rogue_, mage_, knight_)){
        this->gameOverRender();
    }
        
    this->game_window_->display();  
}

void Game::heroWalk(Hero &hero, float delta_time, sf::Clock clock) {
    while((this->game_window_->pollEvent(this->SFML_event_) && this->game_window_->isOpen()) || is_hero_turn){
        int pos_x = 0, pos_y = 0, pos_attack_x = 0, pos_attack_y = 0;
        this->render(delta_time);
        delta_time = clock.restart().asSeconds();

        if(this->SFML_event_.type == sf::Event::Closed){
            this->game_window_->close();
        }
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
                    is_hero_turn = 0;
                    break;

                case sf::Keyboard::Down:
                    pos_y = hero.get_hero_position_y();
                    pos_x = hero.get_hero_position_x();
                    if ((pos_y+1) > 4 || !game_board_->get_tile_at(pos_x, (pos_y+1))->moveableTile()) continue;
                    hero.set_hero_position_y(pos_y+1);
                    game_board_->get_tile_at(pos_x, pos_y)->deleteObjectInTile();
                    game_board_->get_tile_at(pos_x, (pos_y+1))->setObjectInTile("hero");
                    this->current_game_state_->heroTurnPass();
                    is_hero_turn = 0;
                    break;

                case sf::Keyboard::Left:
                    pos_x = hero.get_hero_position_x();
                    pos_y = hero.get_hero_position_y();
                    if ((pos_x-1) < 0 || !game_board_->get_tile_at((pos_x-1), pos_y)->moveableTile()) continue;
                    hero.set_hero_position_x(pos_x-1);
                    game_board_->get_tile_at(pos_x, pos_y)->deleteObjectInTile();
                    game_board_->get_tile_at((pos_x-1), pos_y)->setObjectInTile("hero");
                    this->current_game_state_->heroTurnPass();
                    is_hero_turn = 0;
                    break;

                case sf::Keyboard::Right:
                    pos_x = hero.get_hero_position_x();
                    pos_y = hero.get_hero_position_y();
                    if ((pos_x+1) > 4 || !game_board_->get_tile_at((pos_x+1), pos_y)->moveableTile()) continue;
                    hero.set_hero_position_x(pos_x+1);
                    game_board_->get_tile_at(pos_x, pos_y)->deleteObjectInTile();
                    game_board_->get_tile_at((pos_x+1), pos_y)->setObjectInTile("hero");
                    this->current_game_state_->heroTurnPass();
                    is_hero_turn = 0;
                    break;

                case sf::Keyboard::W:
                    pos_attack_x = hero.get_hero_position_x();
                    pos_attack_y = hero.get_hero_position_y()-1;
                    (my_hordes_.getMonsterInPosition(pos_attack_x, pos_attack_y))->set_monster_hp(50);
                    break;

                case sf::Keyboard::A:
                    break;

                case sf::Keyboard::S:
                    break;

                case sf::Keyboard::D:
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


void Game::monsterTakeAction(int number_of_monsters, float delta_time, sf::Clock clock) {
    if(rogue_.isAlive() || mage_.isAlive() || knight_.isAlive()){
    struct heroes {
        int pos_x;
        int pos_y;
        double distance;
        int distance_x;
        int distance_y;
    };
    heroes hero[3];

    // armazena as coordenadas dos heróis no board
    hero[0].pos_x = knight_.get_hero_position_x();
    hero[0].pos_y = knight_.get_hero_position_y();
    hero[1].pos_x = mage_.get_hero_position_x();
    hero[1].pos_y = mage_.get_hero_position_y();
    hero[2].pos_x = rogue_.get_hero_position_x();
    hero[2].pos_y = rogue_.get_hero_position_y();


    for(int n = 0; n < number_of_monsters; n++) {
        int monster_pos_x = my_hordes_.enemy(n)->get_monster_position_x();
        int monster_pos_y = my_hordes_.enemy(n)->get_monster_position_y();

        // descobre e armazena qual o herói mais próximo ao monstro 
        int nearest_hero_number = 0;
        for (int m = 0; m < 3; m++) {
            hero[m].distance_x = monster_pos_x - hero[m].pos_x;
            hero[m].distance_y = monster_pos_y - hero[m].pos_y;
            hero[m].distance = std::sqrt(std::pow(hero[m].distance_x, 2) + 
            std::pow(hero[m].distance_y, 2));
        }

        heroes nearest_hero = hero[0];

        for (int m = 1; m < 3; m++) {
            if (hero[m].distance < nearest_hero.distance) {
                nearest_hero = hero[m];
                nearest_hero_number = m;
            }
        }

        // decide qual será a ação do monstro sabendo qual o herói mais próximo a ele

        if (nearest_hero.distance == 1) {
            int dmg = my_hordes_.enemy(n)->get_dmg_output();
            if (nearest_hero_number == 0) {
                knight_.set_hero_hp(dmg);
                set_hero_health_bars(0, knight_.get_hero_full_hp(), knight_.get_hero_hp());
            } else if (nearest_hero_number == 1) {
                mage_.set_hero_hp(dmg);
                set_hero_health_bars(1, mage_.get_hero_full_hp(), mage_.get_hero_hp());
            } else if (nearest_hero_number == 2) {
                rogue_.set_hero_hp(dmg);
                set_hero_health_bars(2, rogue_.get_hero_full_hp(), rogue_.get_hero_hp());
            }; 
        }

        // tem que virar else if quando o if acima funcionar
        else if (fabs<int>(nearest_hero.distance_x) >= fabs<int>(nearest_hero.distance_y)) { 
            if (nearest_hero.distance_x > 0) {
                 if (game_board_->get_tile_at((monster_pos_x-1), monster_pos_y)->moveableTile()) {
                    sf::sleep(sf::seconds(0.5));
                    my_hordes_.enemy(n)->set_monster_position_x((monster_pos_x-1));
                    game_board_->get_tile_at(monster_pos_x, monster_pos_y)->deleteObjectInTile();
                    game_board_->get_tile_at((monster_pos_x-1), monster_pos_y)->setObjectInTile("monster");
                }
            } 

            else if (nearest_hero.distance_x < 0) {
                if (game_board_->get_tile_at((monster_pos_x+1), monster_pos_y)->moveableTile()) {
                    sf::sleep(sf::seconds(0.5));
                    my_hordes_.enemy(n)->set_monster_position_x(monster_pos_x+1);
                    game_board_->get_tile_at(monster_pos_x, monster_pos_y)->deleteObjectInTile();
                    game_board_->get_tile_at((monster_pos_x+1), monster_pos_y)->setObjectInTile("monster");
                }
            }
       }

        else if (fabs(nearest_hero.distance_x) < fabs(nearest_hero.distance_y)){
            if (nearest_hero.distance_y > 0) {
                if (game_board_->get_tile_at(monster_pos_x, (monster_pos_y-1))->moveableTile()) {
                    sf::sleep(sf::seconds(0.5));
                    my_hordes_.enemy(n)->set_monster_position_y(monster_pos_y-1);
                    game_board_->get_tile_at(monster_pos_x, monster_pos_y)->deleteObjectInTile();
                    game_board_->get_tile_at(monster_pos_x, (monster_pos_y-1))->setObjectInTile("monster");
                }
            } else if (nearest_hero.distance_y < 0) {
                if (game_board_->get_tile_at(monster_pos_x, (monster_pos_y+1))->moveableTile()) {
                    sf::sleep(sf::seconds(0.5));
                    my_hordes_.enemy(n)->set_monster_position_y(monster_pos_y+1);
                    game_board_->get_tile_at(monster_pos_x, monster_pos_y)->deleteObjectInTile();
                    game_board_->get_tile_at(monster_pos_x, (monster_pos_y+1))->setObjectInTile("monster");
                }
            }
        }

        else {
            // nada deve acontecer 
        }
    
        this->render(delta_time);
        delta_time = clock.restart().asSeconds();
    }
    
    current_game_state_->heroTurnRestart();
    }
}

void Game::setHeroMenu() {
  //Construindo retângulo do menu dos heróis
  background_hero_menu_.setSize(sf::Vector2f(1100, 100));
  background_hero_menu_.setFillColor(sf::Color(70, 46, 64));
  background_hero_menu_.setPosition(sf::Vector2f(50, 600));

  //Construindo textos das opções do menu dos heróis
  font_.loadFromFile("Resources/Retro Gaming.ttf");
  hero_menu_texts_.resize(4);
  hero_menu_printed_texts_ = {"Mover", "Atacar", "Habilidade", "Esperar"};
  hero_menu_texts_position_ = {{70, 620}, {280, 620}, {516, 620}, {860, 620}};
  hero_menu_texts_color_ = {sf::Color::Green, sf::Color(64, 64, 64), sf::Color(64, 64, 64), sf::Color(64, 64, 64)};
  for (unsigned int i = 0; i < hero_menu_texts_.size(); i++) {
    hero_menu_texts_[i].setFont(font_);
    hero_menu_texts_[i].setString(hero_menu_printed_texts_[i]);
    hero_menu_texts_[i].setCharacterSize(50);
    hero_menu_texts_[i].setFillColor(hero_menu_texts_color_[i]);
    hero_menu_texts_[i].setPosition(hero_menu_texts_position_[i]);
  }

  //Inicializando variáveis
  hero_menu_position_ = is_hero_turn = 0;
  keyboard_pressed_hero_menu_ = enter_pressed_hero_menu_ = false;
}

void Game::heroNameTurn(std::string hero_type) {
  font_.loadFromFile("Resources/Retro Gaming.ttf");
  which_hero_.setFont(font_);
  if (hero_type == "delete") {
    which_hero_.setString("");
    which_hero_.setFillColor(sf::Color::Transparent);
  }
  if (hero_type == "knight") {
    which_hero_.setString("Turno do Cavaleiro");
    which_hero_.setPosition(sf::Vector2f(415, 550));
  }
  else if (hero_type == "mage") {
    which_hero_.setString("Turno do Mago");
    which_hero_.setPosition(sf::Vector2f(465, 550));
  }
  else if (hero_type == "rogue") {
    which_hero_.setString("Turno do Ladino");
    which_hero_.setPosition(sf::Vector2f(450, 550));
  }
  which_hero_.setCharacterSize(30);
  which_hero_.setFillColor(sf::Color::White);
}

void Game::chooseDirection(int enter_is_pressed) {
    font_.loadFromFile("Resources/Retro Gaming.ttf");
    which_direction_.setFont(font_);
    if (enter_is_pressed) {
        which_direction_.setString("Cima Baixo Esquerda Direita");
        which_direction_.setFillColor(sf::Color::White);
    }
    else if (!enter_is_pressed) {
        which_direction_.setString("");
        which_direction_.setFillColor(sf::Color::Transparent);
    }
    which_direction_.setCharacterSize(30);
    which_direction_.setPosition(sf::Vector2f(345, 550));
}

void Game::loopHeroMenu(float delta_time, sf::Clock clock) {
  sf::Event event;
  while (game_window_->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      game_window_->close();
    }

    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Right && !keyboard_pressed_hero_menu_) {
        if (hero_menu_position_ < 3) {
          hero_menu_position_++;
          keyboard_pressed_hero_menu_ = true;
          if (hero_menu_position_ == 1) hero_menu_texts_[hero_menu_position_].setFillColor(sf::Color::Red);
          if (hero_menu_position_ == 2) hero_menu_texts_[hero_menu_position_].setFillColor(sf::Color::Blue);
          if (hero_menu_position_ == 3) hero_menu_texts_[hero_menu_position_].setFillColor(sf::Color::Black);
          hero_menu_texts_[hero_menu_position_-1].setFillColor(sf::Color(64, 64, 64));
        }
        keyboard_pressed_hero_menu_ = false;
        enter_pressed_hero_menu_ = false;
      }

      if (event.key.code == sf::Keyboard::Left && !keyboard_pressed_hero_menu_) {
        if (hero_menu_position_ > 0) {
          hero_menu_position_--;
          keyboard_pressed_hero_menu_ = true;
          if (hero_menu_position_ == 0) hero_menu_texts_[hero_menu_position_].setFillColor(sf::Color::Green);
          if (hero_menu_position_ == 1) hero_menu_texts_[hero_menu_position_].setFillColor(sf::Color::Red);
          if (hero_menu_position_ == 2) hero_menu_texts_[hero_menu_position_].setFillColor(sf::Color::Blue);
          hero_menu_texts_[hero_menu_position_+1].setFillColor(sf::Color(64, 64, 64));
        }
        keyboard_pressed_hero_menu_ = false;
        enter_pressed_hero_menu_ = false;
      }

      if (event.key.code == sf::Keyboard::Enter && !enter_pressed_hero_menu_) {
        enter_pressed_hero_menu_ = true;
        heroNameTurn("delete");

        if (hero_menu_position_ == 0) {
            chooseDirection(1);

            if(current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "rogue" && rogue_.isAlive()){
                is_hero_turn = 1;
                heroWalk(rogue_, delta_time, clock);
                enter_pressed_hero_menu_ = false;
            }
            else if(current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "mage" && mage_.isAlive()){
                is_hero_turn = 1;
                heroWalk(mage_, delta_time, clock);
                enter_pressed_hero_menu_ = false;
            }
            else if(current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "knight" && knight_.isAlive()){
                is_hero_turn = 1;
                heroWalk(knight_, delta_time, clock);
                enter_pressed_hero_menu_ = false;
            }
            else {
                this->current_game_state_->heroTurnPass();
                enter_pressed_hero_menu_ = false;
            }
        } 

        if (hero_menu_position_ == 1) {
          selected_choice_ = "attack";
        }

        if (hero_menu_position_ == 2) {
          selected_choice_ = "skill";
        }

        if (hero_menu_position_ == 3) {
          is_hero_turn = 1;
          this->current_game_state_->heroTurnPass();
          is_hero_turn = 0;
          enter_pressed_hero_menu_ = false;
        }

        chooseDirection(0);
      }
    }
  }
}


void Game::playerTurnControl(float delta_time, sf::Clock clock) {
    setHeroMenu();
    while(this->current_game_state_->isPlayerTurn(rogue_.isAlive() + mage_.isAlive() + knight_.isAlive()) && 
                this->game_window_->isOpen()){
        this->heroNameTurn(current_game_state_->whichHeroTurn(rogue_, mage_, knight_));
        this->update();
        this->render(delta_time);
        delta_time = clock.restart().asSeconds();

        loopHeroMenu(delta_time, clock);
    }
}

void Game::run(sf::Clock clock) {
    float delta_time = clock.restart().asSeconds();
    my_hordes_.createHordeEnemies();
    while(this->game_window_->isOpen()) {
        //Conta a passagem de tempo desde a ultima vez que o clock.restart() foi chamado
        delta_time = clock.restart().asSeconds();

        //Essa linha atualiza a tela enquanto o x não for apertado
        this->update();

        //Essa linha de código renderiza o tabuleiro e todas as imagens inclusas nela
        this->render(delta_time);

        //O playerTurnControl garante a movimentação e ataques dos herois durante o turno do jogador
        this->playerTurnControl(delta_time, clock);

        ///O monsterTakeAction movimenta o monstro para a direção dos herois e os ataca
        this->monsterTakeAction(6, delta_time, clock);

        this->gameOverCloseWindow(delta_time, clock);

    }  
}
