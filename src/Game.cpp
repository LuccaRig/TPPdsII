#include "Game.h"
#include "Hero.h"
#include "GameState.h"
#include "Enemies.h"
#include "Skill.h"
#include "Item.h"

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
    init_hero_lvl_ = 0;

    this->initWindow();
    this->current_game_state_ = new GameState();
    game_board_->initializeNumberOfItems();
    // game_board_->set_number_of_items(3);
    // items_.push_back(std::unique_ptr<Item> (new Item(2, 3)));
    // items_.push_back(std::unique_ptr<Item> (new Item(4, 3)));
    // items_.push_back(std::unique_ptr<Item> (new Item(3, 4)));
    // items_.push_back(std::unique_ptr<Item> (new Item(1, 1)));
}

Game::~Game() {
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

void Game::heroFirstLevel() {
    font_.loadFromFile("Resources/Retro Gaming.ttf");
    hero_lvl_.resize(3);
    hero_lvl_printed_ = {"Lvl 1", "Lvl 1", "Lvl 1"};
    hero_lvl_position_= {{218, 20}, {128, 140}, {160, 260}};
    for (unsigned int i = 0; i < hero_lvl_.size(); i++) {
        hero_lvl_[i].setFont(font_);
        hero_lvl_[i].setString(hero_lvl_printed_[i]);
        hero_lvl_[i].setCharacterSize(30);
        hero_lvl_[i].setFillColor(sf::Color::White);
        hero_lvl_[i].setPosition(hero_lvl_position_[i]);
    }
    init_hero_lvl_ = 1;
}

void Game::heroLevel(Hero &hero, int hero_type) {
    int lvl = hero.get_hero_lvl();
    font_.loadFromFile("Resources/Retro Gaming.ttf");
    hero_lvl_.resize(3);
    if (lvl == 2) hero_lvl_printed_[hero_type] = "Lvl 2";
    else if (lvl == 3) hero_lvl_printed_[hero_type] = "Lvl 3";
    else if (lvl == 4) hero_lvl_printed_[hero_type] = "Lvl 4";
    else if (lvl == 5) hero_lvl_printed_[hero_type] = "Lvl 5";
    hero_lvl_position_= {{218, 20}, {128, 140}, {160, 260}};
    for (unsigned int i = 0; i < hero_lvl_.size(); i++) {
        hero_lvl_[i].setFont(font_);
        hero_lvl_[i].setString(hero_lvl_printed_[i]);
        hero_lvl_[i].setCharacterSize(30);
        hero_lvl_[i].setFillColor(sf::Color::White);
        hero_lvl_[i].setPosition(hero_lvl_position_[i]);
    }
    for (auto it : hero_lvl_) {
        this->game_window_->draw(it);
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
    sf::Text press_esc_quit("Aperte qualquer tecla para sair", font_, 20);
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

void Game::playerWinRender() {
    sf::RectangleShape rectangle(sf::Vector2f(800, 200));
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setOutlineColor(sf::Color::White);
    rectangle.setOutlineThickness(2); 

    rectangle.setPosition(200, 540);

    font_.loadFromFile("Resources/Retro Gaming.ttf");
    sf::Text game_over_text("\t\t  Parabens herois!\n Voces venceram a masmorra", font_, 40);
    game_over_text.setFillColor(sf::Color::White);
    sf::Text press_esc_quit("Aperte qualquer tecla para sair", font_, 20);
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

void Game::paleyrWinCloseWindow(float delta_time, sf::Clock clock) {
    while(this->current_game_state_->playerVictory(my_hordes_) && 
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
    if(monster.monsterIsDead()) return;
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

void Game::putItemInBoard(int position_y, int position_x, Item& item,sf::RectangleShape &tileShape) {
    if (item.itemWasUsed()) return;
    if (position_x == item.get_item_position_x() && position_y == item.get_item_position_y()) {
        if (item.get_item_position_x() < 5 && item.get_item_position_y() < 5) {
            if (item.get_item_type() != "empty") {
            game_board_->get_tile_at(position_x, position_y)->setObjectInTile("item");
                item.get_item_sprite().setScale(3.f, 3.f);
                item.get_item_sprite().setPosition(tileShape.getPosition().x + (tileShape.getSize().x - item.get_item_sprite().getLocalBounds().width*3) / 2,
                                                tileShape.getPosition().y + (tileShape.getSize().y - item.get_item_sprite().getLocalBounds().height*3) / 2);
                this->game_window_->draw(item.get_item_sprite());
            }
       }
   }
}

void Game::set_hero_health_bars(int hero, float full_hp, float current_hp) {
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
            sf::RectangleShape currentPosition(sf::Vector2f(currentTile->getTileSize(), currentTile->getTileSize()));
            currentPosition.setOutlineThickness(-2);
            currentPosition.setFillColor(sf::Color::Transparent);
            currentPosition.setOutlineColor(sf::Color::White);
            //Define a cor do quadrado como transparente
            tileShape.setFillColor(sf::Color::Transparent);
            if (current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "rogue" && rogue_.isAlive()) {
                currentPosition.setPosition(board_positionX + rogue_.get_hero_position_x() * currentTile->getTileSize(), 
                                        board_positionY + rogue_.get_hero_position_y() * currentTile->getTileSize());
                this->game_window_->draw(currentPosition);
            }
            else if (current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "mage" && mage_.isAlive()) {
                currentPosition.setPosition(board_positionX + mage_.get_hero_position_x() * currentTile->getTileSize(), 
                                        board_positionY + mage_.get_hero_position_y() * currentTile->getTileSize());
                this->game_window_->draw(currentPosition);
            }
            else if (current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "knight" && knight_.isAlive()) {
                currentPosition.setPosition(board_positionX + knight_.get_hero_position_x() * currentTile->getTileSize(), 
                                        board_positionY + knight_.get_hero_position_y() * currentTile->getTileSize());
                this->game_window_->draw(currentPosition);
            }
            //Desenha o quadrado na janela
            this->game_window_->draw(tileShape);

            putHeroInBoard(i, j, mage_, delta_time, tileShape);
            putHeroInBoard(i, j, knight_, delta_time, tileShape);
            putHeroInBoard(i, j, rogue_, delta_time, tileShape);
            for(int k = 0; k < my_hordes_.hordeSize(); ++k) {
                putMonsterInBoard(i, j, *(my_hordes_.enemy(k)), delta_time, tileShape);
            }
            
            for (int m = 0; m < game_board_->get_number_of_items(); m++) {
                putItemInBoard(j, i, *(items_[m].get()), tileShape);
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
    for (auto it : hero_lvl_) {
        this->game_window_->draw(it);
    }
    if (current_game_state_->isPlayerTurn(rogue_.isAlive() + mage_.isAlive() + knight_.isAlive()) && 
        !current_game_state_->isGameOver(rogue_, mage_, knight_) && !current_game_state_->playerVictory(my_hordes_)) {
        this->game_window_->draw(background_hero_menu_);
        for (auto it : hero_menu_texts_) {
            this->game_window_->draw(it);
        }
        this->game_window_->draw(which_hero_);
        this->game_window_->draw(which_direction_);
        this->game_window_->draw(skill_on_cooldown_);
    }
    if (my_hordes_.get_horde_number() == 1 || my_hordes_.get_horde_number() == 2) {
        this->game_window_->draw(monsters_);
        for (auto it : background_monsters_health_bars_) {
            this->game_window_->draw(it);
        }
        for (auto it : monsters_health_bars_) {
            this->game_window_->draw(it);
        }
    }
    if (my_hordes_.get_horde_number() == 3) {
        this->game_window_->draw(boss_);
        this->game_window_->draw(background_boss_health_bar_);
        this->game_window_->draw(boss_health_bar_);
    }
    this->boardRender(delta_time);
    if(current_game_state_->isGameOver(rogue_, mage_, knight_)){
        this->gameOverRender();
    }
    if(current_game_state_->playerVictory(my_hordes_)) {
        this->playerWinRender();
    }
        
    this->game_window_->display();  
}

void Game::applyItemEffect(int x, int y, Hero& hero) {
    int n = 0;
    for (int i = 0; i < game_board_->get_number_of_items(); i++) {
        if ((items_[i]->get_item_position_x() == x) && (items_[i]->get_item_position_y()) == y) {
            n = i;            
            break;
        }
    }
    items_[n]->set_item_to_used();
    std::string item_type = items_[n]->get_item_type();
    int item_effect = items_[n]->get_item_effect();
    if (item_type == "heal") {
        hero.set_hero_hp(-item_effect);
        set_hero_health_bars(hero.get_hero_number(), hero.get_hero_full_hp(), hero.get_hero_hp());
    } else if (item_type == "dmgBuff") {
        hero.set_hero_attack(item_effect);
    } else if (item_type == "spellBuff") {
        hero.set_hero_special_attack(item_effect);
    }
}

void Game::heroWalk(Hero &hero, float delta_time, sf::Clock clock) {
    while((this->game_window_->pollEvent(this->SFML_event_) && this->game_window_->isOpen()) || is_hero_turn){
        int pos_x = 0, pos_y = 0;
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
                    if ((pos_y-1) < 0 || !game_board_->get_tile_at(pos_x, (pos_y-1))->moveableTile()) {
                        is_hero_turn = 0;
                        break;
                    }
                    hero.set_hero_position_y(pos_y-1);
                    game_board_->get_tile_at(pos_x, pos_y)->deleteObjectInTile();

                    if (game_board_->get_tile_at(pos_x, pos_y-1)->getObjectInTile() == "item") {
                        applyItemEffect(pos_x, pos_y-1, hero);
                    }
                    game_board_->get_tile_at(pos_x, (pos_y-1))->setObjectInTile("hero");
                    heroSkillCooldownDecreases(hero);
                    this->current_game_state_->heroTurnPass();
                    is_hero_turn = 0;
                    break;

                case sf::Keyboard::Down:
                    pos_y = hero.get_hero_position_y();
                    pos_x = hero.get_hero_position_x();
                    if ((pos_y+1) > 4 || !game_board_->get_tile_at(pos_x, (pos_y+1))->moveableTile()) {
                        is_hero_turn = 0;
                        break;
                    }
                    hero.set_hero_position_y(pos_y+1);
                    game_board_->get_tile_at(pos_x, pos_y)->deleteObjectInTile();

                    if (game_board_->get_tile_at(pos_x, pos_y+1)->getObjectInTile() == "item") {
                        applyItemEffect(pos_x, pos_y+1, hero);
                    }
                    game_board_->get_tile_at(pos_x, (pos_y+1))->setObjectInTile("hero");
                    heroSkillCooldownDecreases(hero);
                    this->current_game_state_->heroTurnPass();
                    is_hero_turn = 0;
                    break;

                case sf::Keyboard::Left:
                    pos_x = hero.get_hero_position_x();
                    pos_y = hero.get_hero_position_y();
                    if ((pos_x-1) < 0 || !game_board_->get_tile_at((pos_x-1), pos_y)->moveableTile()) {
                        is_hero_turn = 0;
                        break;
                    }
                    hero.set_hero_position_x(pos_x-1);
                    game_board_->get_tile_at(pos_x, pos_y)->deleteObjectInTile();

                    if (game_board_->get_tile_at(pos_x-1, pos_y)->getObjectInTile() == "item") {
                        applyItemEffect(pos_x-1, pos_y, hero);
                    }
                    game_board_->get_tile_at((pos_x-1), pos_y)->setObjectInTile("hero");
                    heroSkillCooldownDecreases(hero);
                    this->current_game_state_->heroTurnPass();
                    is_hero_turn = 0;
                    break;

                case sf::Keyboard::Right:
                    pos_x = hero.get_hero_position_x();
                    pos_y = hero.get_hero_position_y();
                    if ((pos_x+1) > 4 || !game_board_->get_tile_at((pos_x+1), pos_y)->moveableTile()) {
                        is_hero_turn = 0;
                        break;
                    }
                    hero.set_hero_position_x(pos_x+1);
                    game_board_->get_tile_at(pos_x, pos_y)->deleteObjectInTile();

                    if (game_board_->get_tile_at(pos_x+1, pos_y)->getObjectInTile() == "item") {
                        applyItemEffect(pos_x+1, pos_y, hero);
                    }
                    game_board_->get_tile_at((pos_x+1), pos_y)->setObjectInTile("hero");
                    heroSkillCooldownDecreases(hero);
                    this->current_game_state_->heroTurnPass();
                    is_hero_turn = 0;
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

void Game::heroAttack(Hero &hero, float delta_time, sf::Clock clock) {
    while((this->game_window_->pollEvent(this->SFML_event_) && this->game_window_->isOpen()) || is_hero_turn){
        int pos_to_attack_x = 0, pos_to_attack_y = 0;
        Monster* monster_to_be_attacked;
        this->render(delta_time);
        delta_time = clock.restart().asSeconds();

        if(this->SFML_event_.type == sf::Event::Closed){
            this->game_window_->close();
        }
        if(this->SFML_event_.type == sf::Event::KeyPressed){ 
            switch (this->SFML_event_.key.code) {
                case sf::Keyboard::Up:
                    pos_to_attack_x = hero.get_hero_position_x();
                    pos_to_attack_y = hero.get_hero_position_y()-1;
                    if(pos_to_attack_y < 0) continue;
                    if(!game_board_->get_tile_at(pos_to_attack_x, pos_to_attack_y)->monsterIsInTile()) {
                        is_hero_turn = 0;
                        break;
                    }
                    monster_to_be_attacked = my_hordes_.getMonsterInPosition(pos_to_attack_x, pos_to_attack_y);

                    (*monster_to_be_attacked).set_monster_hp<Item>(game_board_, items_, hero.get_hero_attack());

                    if (monster_to_be_attacked->monsterIsDead()) {
                        hero.set_current_exp(monster_to_be_attacked->get_exp_drop(), hero.get_hero_type());
                        set_hero_health_bars(hero.get_hero_number(), hero.get_hero_full_hp(), hero.get_hero_hp());
                    }
                    setMonstersHealthBars(monster_to_be_attacked->get_monster_number(), 
                                            monster_to_be_attacked->get_monster_full_hp(), monster_to_be_attacked->get_monster_hp());
                    
                    heroSkillCooldownDecreases(hero);
                    this->current_game_state_->heroTurnPass();
                    is_hero_turn = 0;
                    break;

                case sf::Keyboard::Down:
                    pos_to_attack_x = hero.get_hero_position_x();
                    pos_to_attack_y = hero.get_hero_position_y()+1;
                    if(pos_to_attack_y > 4) continue;
                    if(!game_board_->get_tile_at(pos_to_attack_x, pos_to_attack_y)->monsterIsInTile()) {
                        is_hero_turn = 0;
                        break;
                    }
                    monster_to_be_attacked = my_hordes_.getMonsterInPosition(pos_to_attack_x, pos_to_attack_y);

                    (*monster_to_be_attacked).set_monster_hp<Item>(game_board_, items_, hero.get_hero_attack());

                    if (monster_to_be_attacked->monsterIsDead()) {
                        hero.set_current_exp(monster_to_be_attacked->get_exp_drop(), hero.get_hero_type());
                        set_hero_health_bars(hero.get_hero_number(), hero.get_hero_full_hp(), hero.get_hero_hp());
                    }
                    setMonstersHealthBars(monster_to_be_attacked->get_monster_number(), 
                                            monster_to_be_attacked->get_monster_full_hp(), monster_to_be_attacked->get_monster_hp());

                    heroSkillCooldownDecreases(hero);
                    this->current_game_state_->heroTurnPass();
                    is_hero_turn = 0;
                    break;

                case sf::Keyboard::Left: 
                    pos_to_attack_x = hero.get_hero_position_x()-1;
                    pos_to_attack_y = hero.get_hero_position_y();
                    if(pos_to_attack_x < 0) continue;
                    if(!game_board_->get_tile_at(pos_to_attack_x, pos_to_attack_y)->monsterIsInTile()) {
                        is_hero_turn = 0;
                        break;
                    }
                    monster_to_be_attacked = my_hordes_.getMonsterInPosition(pos_to_attack_x, pos_to_attack_y);

                    (*monster_to_be_attacked).set_monster_hp<Item>(game_board_, items_, hero.get_hero_attack());
                
                    if (monster_to_be_attacked->monsterIsDead()) {
                        hero.set_current_exp(monster_to_be_attacked->get_exp_drop(), hero.get_hero_type());
                        set_hero_health_bars(hero.get_hero_number(), hero.get_hero_full_hp(), hero.get_hero_hp());
                    }
                    setMonstersHealthBars(monster_to_be_attacked->get_monster_number(), 
                                            monster_to_be_attacked->get_monster_full_hp(), monster_to_be_attacked->get_monster_hp());
                
                    heroSkillCooldownDecreases(hero);
                    this->current_game_state_->heroTurnPass();
                    is_hero_turn = 0;
                    break;

                case sf::Keyboard::Right:
                    pos_to_attack_x = hero.get_hero_position_x()+1;
                    pos_to_attack_y = hero.get_hero_position_y();
                    if(pos_to_attack_x > 4) continue;
                    if(!game_board_->get_tile_at(pos_to_attack_x, pos_to_attack_y)->monsterIsInTile()) {
                        is_hero_turn = 0;
                        break;
                    }
                    monster_to_be_attacked = my_hordes_.getMonsterInPosition(pos_to_attack_x, pos_to_attack_y);

                    (*monster_to_be_attacked).set_monster_hp<Item>(game_board_, items_, hero.get_hero_attack());

                    if (monster_to_be_attacked->monsterIsDead()) {
                        hero.set_current_exp(monster_to_be_attacked->get_exp_drop(), hero.get_hero_type());
                        set_hero_health_bars(hero.get_hero_number(), hero.get_hero_full_hp(), hero.get_hero_hp());
                    }
                    setMonstersHealthBars(monster_to_be_attacked->get_monster_number(), 
                                            monster_to_be_attacked->get_monster_full_hp(), monster_to_be_attacked->get_monster_hp());

                    heroSkillCooldownDecreases(hero);
                    this->current_game_state_->heroTurnPass();
                    is_hero_turn = 0;
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

void Game::heroUseBuffSkill(int hero_number, std::string hero_type, Hero &hero) {
  if (hero_type == "knight") {
    if (hero.get_skill_cooldown() == 2) {
      Skill skill(hero_type, hero.get_hero_special_attack());
      hero.set_hero_hp(-skill.skill_heal());
      set_hero_health_bars(hero_number, hero.get_hero_full_hp(), hero.get_hero_hp());
      hero.set_hero_attack(skill.skill_buff());
      hero.restartSkillCooldown();
      this->current_game_state_->heroTurnPass();
    }
    else {
      hero.decreaseSkillCooldown();
      this->current_game_state_->heroTurnPass();
    }
  }
  else if (hero_type == "rogue") {
    if (hero.get_skill_cooldown() == 1) {
      Skill skill(hero_type, hero.get_hero_special_attack());
      hero.set_hero_hp(-skill.skill_heal());
      set_hero_health_bars(hero_number, hero.get_hero_full_hp(), hero.get_hero_hp());
      hero.set_hero_attack(skill.skill_buff());
      hero.restartSkillCooldown();
      this->current_game_state_->heroTurnPass();
    }
    else {
      hero.decreaseSkillCooldown();
      this->current_game_state_->heroTurnPass();
    }
  }
}

void Game::heroUseDamageSkill(std::string hero_type, Hero &hero) {
  if (hero.get_skill_cooldown() == 2) {
    Skill skill(hero_type, hero.get_hero_special_attack());
    int pos_to_attack_x = 0, pos_to_attack_y = 0;
    Monster* monster_to_be_attacked;

    pos_to_attack_x = hero.get_hero_position_x();
    pos_to_attack_y = hero.get_hero_position_y();

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
        if (i == pos_to_attack_y || j == pos_to_attack_x) {
            if(game_board_->get_tile_at(j, i)->monsterIsInTile()) {
            monster_to_be_attacked = my_hordes_.getMonsterInPosition(j, i);
            
            (*monster_to_be_attacked).set_monster_hp<Item>(game_board_, items_, skill.skill_damage());

            if (monster_to_be_attacked->monsterIsDead()) {
                hero.set_current_exp(monster_to_be_attacked->get_exp_drop(), hero.get_hero_type());
                set_hero_health_bars(hero.get_hero_number(), hero.get_hero_full_hp(), hero.get_hero_hp());
            }
            setMonstersHealthBars(monster_to_be_attacked->get_monster_number(), 
                                    monster_to_be_attacked->get_monster_full_hp(), monster_to_be_attacked->get_monster_hp());

            }
        }
        }
    }
    hero.restartSkillCooldown();
    this->current_game_state_->heroTurnPass();
  }
  else {
    hero.decreaseSkillCooldown();
    this->current_game_state_->heroTurnPass();
  }
}

void Game::heroSkillCooldownDecreases(Hero &hero) {
    if (hero.get_hero_type() == "knight" || hero.get_hero_type() == "mage") {
        if (hero.get_skill_cooldown() < 2) {
            hero.decreaseSkillCooldown();
        }
    }
    else if (hero.get_hero_type() == "rogue") {
        if (hero.get_skill_cooldown() < 1) {
            hero.decreaseSkillCooldown();
        }
    }
}

bool Game::isSkillOnCooldown() {
  if (this->current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "rogue" && 
      rogue_.get_skill_cooldown() != 1) return true;
  else if (this->current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "mage" && 
           mage_.get_skill_cooldown() != 2) return true;
  else if (this->current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "knight" && 
           knight_.get_skill_cooldown() != 2) return true;
  return false;
}

bool Game::isNextSkillOnCooldown() {
  if (rogue_.isAlive() && mage_.isAlive() && knight_.isAlive()) {
    if (this->current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "rogue" &&
        mage_.get_skill_cooldown() != 2) return true;
    else if (this->current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "mage" &&
             knight_.get_skill_cooldown() != 2) return true;
    else if (this->current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "knight" &&
             rogue_.get_skill_cooldown() != 1) return true;
    return false;
  }
  else if (!rogue_.isAlive() && mage_.isAlive() && knight_.isAlive()) {
    if (this->current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "mage" &&
        knight_.get_skill_cooldown() != 2) return true;
    else if (this->current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "knight" &&
             mage_.get_skill_cooldown() != 2) return true;
    return false;
  }
  else if (rogue_.isAlive() && !mage_.isAlive() && knight_.isAlive()) {
    if (this->current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "rogue" &&
        knight_.get_skill_cooldown() != 2) return true;
    else if (this->current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "knight" &&
             rogue_.get_skill_cooldown() != 1) return true;
    return false;
  }
    else if (rogue_.isAlive() && mage_.isAlive() && !knight_.isAlive()) {
    if (this->current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "rogue" &&
        mage_.get_skill_cooldown() != 2) return true;
    else if (this->current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "mage" &&
             rogue_.get_skill_cooldown() != 1) return true;
    return false;
  }
  return false;
}

void Game::writeCooldown(int is_on_cooldown) {
  font_.loadFromFile("Resources/Retro Gaming.ttf");
  skill_on_cooldown_.setFont(font_);
  if (is_on_cooldown) {
    skill_on_cooldown_.setString("Em Cooldown");
    skill_on_cooldown_.setFillColor(sf::Color::White);
  }
  else if (!is_on_cooldown) {
    skill_on_cooldown_.setString(" ");
    skill_on_cooldown_.setFillColor(sf::Color::Transparent);
  }
  skill_on_cooldown_.setCharacterSize(20);
  skill_on_cooldown_.setPosition(sf::Vector2f(600, 600));
}

void Game::initMonstersHealthBars() {
    font_.loadFromFile("Resources/Retro Gaming.ttf");
    monsters_.setFont(font_);
    monsters_.setString("Monstros");
    monsters_.setCharacterSize(30);
    monsters_.setFillColor(sf::Color::White);
    monsters_.setPosition(sf::Vector2f(1009, 20));

    background_monsters_health_bars_.resize(my_hordes_.hordeSize());
    monsters_health_bars_.resize(my_hordes_.hordeSize());
    monsters_health_bars_position_ = {{1050, 70}, {1050, 100}, {1050, 130}, {1050, 160}, {1050, 190}, {1050, 220}};
    for (unsigned int i = 0; i < monsters_health_bars_.size(); i++) {
        monsters_health_bars_[i].setSize(sf::Vector2f(100, 20));
        monsters_health_bars_[i].setFillColor(sf::Color(128, 0, 0));
        monsters_health_bars_[i].setPosition(monsters_health_bars_position_[i]);
        background_monsters_health_bars_[i].setSize(sf::Vector2f(100, 20));
        background_monsters_health_bars_[i].setFillColor(sf::Color::Black);
        background_monsters_health_bars_[i].setPosition(monsters_health_bars_position_[i]);
    }


    boss_.setFont(font_);
    boss_.setString("Vida do Boss");
    boss_.setCharacterSize(30);
    boss_.setFillColor(sf::Color::White);
    boss_.setPosition(sf::Vector2f(900, 20));

    boss_health_bar_.setSize(sf::Vector2f(220, 30));
    boss_health_bar_.setFillColor(sf::Color(128, 0, 0));
    boss_health_bar_.setPosition(sf::Vector2f(900, 70));
    background_boss_health_bar_.setSize(sf::Vector2f(220, 30));
    background_boss_health_bar_.setFillColor(sf::Color::Black);
    background_boss_health_bar_.setPosition(sf::Vector2f(900, 70));
}

void Game::setMonstersHealthBars(int damaged_monster, float full_hp, float current_hp) {
    if(my_hordes_.get_horde_number() == 3 && damaged_monster == 8)  boss_health_bar_.setSize(sf::Vector2f(220*current_hp/full_hp, 30));
    else monsters_health_bars_[damaged_monster].setSize(sf::Vector2f(100*current_hp/full_hp, 20));
}

void Game::monsterMove(int enemy_number, int distance_x, int distance_y, int pos_x, int pos_y, std::string direction, bool recursion) {
    if (direction == "x") {
        if ((distance_x == 0) && !(recursion)) {
            if (game_board_->get_tile_at((pos_x+1), pos_y)->moveableTile() && 
                game_board_->get_tile_at((pos_x+1), pos_y)->getObjectInTile() != "item") {
                sf::sleep(sf::seconds(0.5));
                my_hordes_.enemy(enemy_number)->set_monster_position_x((pos_x+1));
                game_board_->get_tile_at(pos_x, pos_y)->deleteObjectInTile();
                game_board_->get_tile_at((pos_x+1), pos_y)->setObjectInTile("monster");
            } else if (game_board_->get_tile_at((pos_x-1), pos_y)->moveableTile() && 
                game_board_->get_tile_at((pos_x-1), pos_y)->getObjectInTile() != "item") {
                sf::sleep(sf::seconds(0.5));
                my_hordes_.enemy(enemy_number)->set_monster_position_x((pos_x-1));
                game_board_->get_tile_at(pos_x, pos_y)->deleteObjectInTile();
                game_board_->get_tile_at((pos_x-1), pos_y)->setObjectInTile("monster");
            }
        }
        else if (distance_x > 0) {
            if (game_board_->get_tile_at((pos_x-1), pos_y)->moveableTile()) {
                if ((game_board_->get_tile_at((pos_x-1), pos_y)->getObjectInTile() == "item") && recursion) {
                    monsterMove(enemy_number, distance_x, distance_y, pos_x, pos_y, "y", false);
                } else if (game_board_->get_tile_at((pos_x-1), pos_y)->getObjectInTile() != "item") {
                    sf::sleep(sf::seconds(0.5));
                    my_hordes_.enemy(enemy_number)->set_monster_position_x((pos_x-1));
                    game_board_->get_tile_at(pos_x, pos_y)->deleteObjectInTile();
                    game_board_->get_tile_at((pos_x-1), pos_y)->setObjectInTile("monster");
                }
            }
        } else if (distance_x < 0) {
            if (game_board_->get_tile_at((pos_x+1), pos_y)->moveableTile()) {
                if ((game_board_->get_tile_at((pos_x+1), pos_y)->getObjectInTile() == "item") && recursion) {
                    monsterMove(enemy_number, distance_x, distance_y, pos_x, pos_y, "y", false);
                } else if (game_board_->get_tile_at((pos_x+1), pos_y)->getObjectInTile() != "item") {
                    sf::sleep(sf::seconds(0.5));
                    my_hordes_.enemy(enemy_number)->set_monster_position_x(pos_x+1);
                    game_board_->get_tile_at(pos_x, pos_y)->deleteObjectInTile();
                    game_board_->get_tile_at((pos_x+1), pos_y)->setObjectInTile("monster");
                }
            }
        }
        } else if (direction == "y") {
            if ((distance_y == 0) && !(recursion)) {
            if (game_board_->get_tile_at(pos_x, (pos_y+1))->moveableTile() && 
            game_board_->get_tile_at(pos_x, (pos_y+1))->getObjectInTile() != "item") {
                sf::sleep(sf::seconds(0.5));
                my_hordes_.enemy(enemy_number)->set_monster_position_y((pos_y+1));
                game_board_->get_tile_at(pos_x, pos_y)->deleteObjectInTile();
                game_board_->get_tile_at(pos_x, (pos_y+1))->setObjectInTile("monster");
            } else if (game_board_->get_tile_at(pos_x, (pos_y-1))->moveableTile() && 
            game_board_->get_tile_at(pos_x, (pos_y-1))->getObjectInTile() != "item") {
                sf::sleep(sf::seconds(0.5));
                my_hordes_.enemy(enemy_number)->set_monster_position_y((pos_y+1));
                game_board_->get_tile_at(pos_x, pos_y)->deleteObjectInTile();
                game_board_->get_tile_at(pos_x, (pos_y-1))->setObjectInTile("monster");
            }
            }
            else if (distance_y > 0) {
            if (game_board_->get_tile_at(pos_x, (pos_y-1))->moveableTile()) {
                if ((game_board_->get_tile_at(pos_x, (pos_y-1))->getObjectInTile() == "item") && recursion) {
                    monsterMove(enemy_number, distance_x, distance_y, pos_x, pos_y, "x", false);
                } else if (game_board_->get_tile_at(pos_x, (pos_y-1))->getObjectInTile() != "item") {
                    sf::sleep(sf::seconds(0.5));
                    my_hordes_.enemy(enemy_number)->set_monster_position_y(pos_y-1);
                    game_board_->get_tile_at(pos_x, pos_y)->deleteObjectInTile();
                    game_board_->get_tile_at(pos_x, (pos_y-1))->setObjectInTile("monster");
                }
            }
        } else if (distance_y < 0) {
            if (game_board_->get_tile_at(pos_x, (pos_y+1))->moveableTile()) {
                if ((game_board_->get_tile_at(pos_x, (pos_y+1))->getObjectInTile() == "item") && recursion) {
                    monsterMove(enemy_number, distance_x, distance_y, pos_x, pos_y, "x", false);
                } else if (game_board_->get_tile_at(pos_x, (pos_y+1))->getObjectInTile() != "item") {
                    sf::sleep(sf::seconds(0.5));
                    my_hordes_.enemy(enemy_number)->set_monster_position_y(pos_y+1);
                    game_board_->get_tile_at(pos_x, pos_y)->deleteObjectInTile();
                    game_board_->get_tile_at(pos_x, (pos_y+1))->setObjectInTile("monster");
                }
            }
        }
    }
}


void Game::monsterTakeAction(int number_of_monsters, float delta_time, sf::Clock clock) {
    if((rogue_.isAlive() || mage_.isAlive() || knight_.isAlive()) && !current_game_state_->playerVictory(my_hordes_)){
        
        if(this->my_hordes_.bossIsAlive()){
            this->my_hordes_.eyeSpawn(game_board_);
            this->my_hordes_.bossTurnIncrement();
        }
    
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
        if(!my_hordes_.enemy(n)->monsterIsDead()){
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
                monsterMove(n, nearest_hero.distance_x, nearest_hero.distance_y, monster_pos_x, monster_pos_y, "x", true);
        //         if (nearest_hero.distance_x > 0) {
        //             if (game_board_->get_tile_at((monster_pos_x-1), monster_pos_y)->moveableTile()) {
        //                 sf::sleep(sf::seconds(0.5));
        //                 my_hordes_.enemy(n)->set_monster_position_x((monster_pos_x-1));
        //                 game_board_->get_tile_at(monster_pos_x, monster_pos_y)->deleteObjectInTile();
        //                 game_board_->get_tile_at((monster_pos_x-1), monster_pos_y)->setObjectInTile("monster");
        //             }
        //         } 

        //         else if (nearest_hero.distance_x < 0) {
        //             if (game_board_->get_tile_at((monster_pos_x+1), monster_pos_y)->moveableTile()) {
        //                 sf::sleep(sf::seconds(0.5));
        //                 my_hordes_.enemy(n)->set_monster_position_x(monster_pos_x+1);
        //                 game_board_->get_tile_at(monster_pos_x, monster_pos_y)->deleteObjectInTile();
        //                 game_board_->get_tile_at((monster_pos_x+1), monster_pos_y)->setObjectInTile("monster");
        //             }
        //         }
            }

            else if (fabs(nearest_hero.distance_x) < fabs(nearest_hero.distance_y)) {
                monsterMove(n, nearest_hero.distance_x, nearest_hero.distance_y, monster_pos_x, monster_pos_y, "y", true);
                // if (nearest_hero.distance_y > 0) {
                //     if (game_board_->get_tile_at(monster_pos_x, (monster_pos_y-1))->moveableTile()) {
                //         sf::sleep(sf::seconds(0.5));
                //         my_hordes_.enemy(n)->set_monster_position_y(monster_pos_y-1);
                //         game_board_->get_tile_at(monster_pos_x, monster_pos_y)->deleteObjectInTile();
                //         game_board_->get_tile_at(monster_pos_x, (monster_pos_y-1))->setObjectInTile("monster");
                //     }
                // } else if (nearest_hero.distance_y < 0) {
                //     if (game_board_->get_tile_at(monster_pos_x, (monster_pos_y+1))->moveableTile()) {
                //         sf::sleep(sf::seconds(0.5));
                //         my_hordes_.enemy(n)->set_monster_position_y(monster_pos_y+1);
                //         game_board_->get_tile_at(monster_pos_x, monster_pos_y)->deleteObjectInTile();
                //         game_board_->get_tile_at(monster_pos_x, (monster_pos_y+1))->setObjectInTile("monster");
                //     }
                // }
            }

            else {
                // nada deve acontecer 
            }
        
            this->render(delta_time);
            delta_time = clock.restart().asSeconds();
        }
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
          if (hero_menu_position_ == 1) {
            hero_menu_texts_[hero_menu_position_].setFillColor(sf::Color::Red);
            writeCooldown(0);
          }
          if (hero_menu_position_ == 2) {
            hero_menu_texts_[hero_menu_position_].setFillColor(sf::Color::Blue);
            if (isSkillOnCooldown()) writeCooldown(1);
          }
          if (hero_menu_position_ == 3) {
            hero_menu_texts_[hero_menu_position_].setFillColor(sf::Color::Black);
            writeCooldown(0);
          }
          hero_menu_texts_[hero_menu_position_-1].setFillColor(sf::Color(64, 64, 64));
        }
        keyboard_pressed_hero_menu_ = false;
        enter_pressed_hero_menu_ = false;
      }

      if (event.key.code == sf::Keyboard::Left && !keyboard_pressed_hero_menu_) {
        if (hero_menu_position_ > 0) {
          hero_menu_position_--;
          keyboard_pressed_hero_menu_ = true;
          if (hero_menu_position_ == 0) {
            hero_menu_texts_[hero_menu_position_].setFillColor(sf::Color::Green);
            writeCooldown(0);
          }
          if (hero_menu_position_ == 1) {
            hero_menu_texts_[hero_menu_position_].setFillColor(sf::Color::Red);
            writeCooldown(0);
          }          
          if (hero_menu_position_ == 2) {
            hero_menu_texts_[hero_menu_position_].setFillColor(sf::Color::Blue);
            if (isSkillOnCooldown()) writeCooldown(1);
          }          
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
                //my_hordes_.createHordeEnemies(rogue_, mage_, knight_);
                enter_pressed_hero_menu_ = false;
            }
            else if(current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "mage" && mage_.isAlive()){
                is_hero_turn = 1;
                heroWalk(mage_, delta_time, clock);
                //my_hordes_.createHordeEnemies(rogue_, mage_, knight_);
                enter_pressed_hero_menu_ = false;
            }
            else if(current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "knight" && knight_.isAlive()){
                is_hero_turn = 1;
                heroWalk(knight_, delta_time, clock);
                //my_hordes_.createHordeEnemies(rogue_, mage_, knight_);
                enter_pressed_hero_menu_ = false;
            }
            else {
                this->current_game_state_->heroTurnPass();
                enter_pressed_hero_menu_ = false;
            }
        } 

        if (hero_menu_position_ == 1) {
          chooseDirection(1);

          if(current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "rogue" && rogue_.isAlive()){
                is_hero_turn = 1;
                heroAttack(rogue_, delta_time, clock);
                heroLevel(rogue_, rogue_.get_hero_number());
                //my_hordes_.createHordeEnemies(rogue_, mage_, knight_);
                enter_pressed_hero_menu_ = false;
            }
            else if(current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "mage" && mage_.isAlive()){
                is_hero_turn = 1;
                heroAttack(mage_, delta_time, clock);
                heroLevel(mage_, mage_.get_hero_number());
                //my_hordes_.createHordeEnemies(rogue_, mage_, knight_);
                enter_pressed_hero_menu_ = false;
            }
            else if(current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "knight" && knight_.isAlive()){
                is_hero_turn = 1;
                heroAttack(knight_, delta_time, clock);
                heroLevel(knight_, knight_.get_hero_number());
                //my_hordes_.createHordeEnemies(rogue_, mage_, knight_);
                enter_pressed_hero_menu_ = false;
            }
            else {
                this->current_game_state_->heroTurnPass();
                enter_pressed_hero_menu_ = false;
            }
        }

        if (hero_menu_position_ == 2) {
          writeCooldown(0);
          if (isNextSkillOnCooldown() && !this->current_game_state_->isLastHeroTurn(rogue_.isAlive()+mage_.isAlive()+knight_.isAlive()))  {
            writeCooldown(1);
          }

          if(current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "rogue" && rogue_.isAlive()) {
            heroUseBuffSkill(2, "rogue", rogue_);
            //my_hordes_.createHordeEnemies(rogue_, mage_, knight_);
            enter_pressed_hero_menu_ = false;
          }
          else if(current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "knight" && knight_.isAlive()) {
            heroUseBuffSkill(0, "knight", knight_);
            //my_hordes_.createHordeEnemies(rogue_, mage_, knight_);
            enter_pressed_hero_menu_ = false;
          }
          else if(current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "mage" && mage_.isAlive()) {
            heroUseDamageSkill("mage", mage_);
            heroLevel(mage_, mage_.get_hero_number());
            //my_hordes_.createHordeEnemies(rogue_, mage_, knight_);
            enter_pressed_hero_menu_ = false;
          }
          else {
            this->current_game_state_->heroTurnPass();
            enter_pressed_hero_menu_ = false;
          }
        }

        if (hero_menu_position_ == 3) {
          if(current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "rogue" && rogue_.isAlive()) {
            is_hero_turn = 1;
            heroSkillCooldownDecreases(rogue_);
            this->current_game_state_->heroTurnPass();
            is_hero_turn = 0;
            enter_pressed_hero_menu_ = false;
          }
          else if(current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "knight" && knight_.isAlive()) {
            is_hero_turn = 1;
            heroSkillCooldownDecreases(knight_);
            this->current_game_state_->heroTurnPass();
            is_hero_turn = 0;
            enter_pressed_hero_menu_ = false;
          }
          else if(current_game_state_->whichHeroTurn(rogue_, mage_, knight_) == "mage" && mage_.isAlive()) {
            is_hero_turn = 1;
            heroSkillCooldownDecreases(mage_);
            this->current_game_state_->heroTurnPass();
            is_hero_turn = 0;
            enter_pressed_hero_menu_ = false;
          }
        }

        chooseDirection(0);
      }
    }
  }
}


void Game::playerTurnControl(float delta_time, sf::Clock clock) {
    if (!init_hero_lvl_) heroFirstLevel();
    setHeroMenu();
    while(this->current_game_state_->isPlayerTurn(rogue_.isAlive() + mage_.isAlive() + knight_.isAlive()) && 
                this->game_window_->isOpen() && !current_game_state_->playerVictory(my_hordes_)){
        this->heroNameTurn(current_game_state_->whichHeroTurn(rogue_, mage_, knight_));
        this->update();
        this->render(delta_time);
        delta_time = clock.restart().asSeconds();

        loopHeroMenu(delta_time, clock);
    }
}

void Game::run(sf::Clock clock) {
    float delta_time = clock.restart().asSeconds();
    if (my_hordes_.get_horde_number() == 0) initMonstersHealthBars();
    my_hordes_.createHordeEnemies(game_board_, rogue_, mage_, knight_);
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
        this->monsterTakeAction(my_hordes_.hordeSize(), delta_time, clock);

        if (my_hordes_.get_horde_number() == 1 && my_hordes_.allEnemiesAreDead()) initMonstersHealthBars();
        my_hordes_.createHordeEnemies(game_board_, rogue_, mage_, knight_);
        if (my_hordes_.get_horde_number() == 2 && my_hordes_.allEnemiesAreDead()) initMonstersHealthBars();

        this->paleyrWinCloseWindow(delta_time, clock);
        //Se for GameOver a janela será fechada com qualquer tecla apertada
        this->gameOverCloseWindow(delta_time, clock);

    }  
}
