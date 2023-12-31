#include "Monster.h"

#include <string>

#include "Board.h"
#include "Item.h"
#include "Hero.h"


    Monster::Monster (std::string monster_type) {
        monster_type_ = monster_type;
        monster_sprite_ = sf::Sprite();

        number_of_frames_ = 4;
        current_frame_ = 0;
        animation_timer_ = 0.0f;
        monster_position_x_ = 0;
        monster_position_y_ = 0;
        monster_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));

        if (monster_type_ == "bloody abomination 1" || monster_type_ == "bloody abomination 2") {
            if (monster_type_ == "bloody abomination 1") monster_number_ = 0;
            if (monster_type_ == "bloody abomination 2") monster_number_ = 2;
            monster_hp_ = monster_full_hp_ = 18;
            monster_dmg_ = 10;
            monster_exp_drop_ = 5;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/BloodyAbominationIdleSide.png");  
        }
        else if (monster_type_ == "death knight") {
            monster_hp_ = monster_full_hp_ = 32;
            monster_dmg_ = 7;
            monster_exp_drop_ = 6;
            monster_number_ = 4;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/DeathKnightIdleSide.png"); 
        } 
        else if (monster_type_ == "stalker") {
            monster_hp_ = monster_full_hp_ = 15;
            monster_dmg_ = 8;
            monster_exp_drop_ = 4;
            monster_number_ = 1;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/SkeweringStalker.png");
        }
        else if (monster_type_ == "floating eye") {
            monster_hp_ = monster_full_hp_ = 25;
            monster_dmg_ = 5;
            monster_exp_drop_ = 3;
            monster_number_ = 4;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/FloatingEye.png");
        }
        else if (monster_type_ == "sand golem") {
            monster_hp_ = monster_full_hp_ = 42;
            monster_dmg_ = 2;
            monster_exp_drop_ = 3;
            monster_number_ = 1;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/SandGolemIdleSide.png");   
        }
        else if (monster_type_ == "ghastly beholder 1" || monster_type_ == "ghastly beholder 2") {
            if (monster_type_ == "ghastly beholder 1") monster_number_ = 3;
            if (monster_type_ == "ghastly beholder 2") monster_number_ = 5;
            monster_hp_ = monster_full_hp_ = 14;
            monster_dmg_ = 3;
            monster_exp_drop_ = 1;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/GhastlyBeholderIdleSide.png");  
        }
        else if (monster_type_ == "unholy skull 1" || monster_type_ == "unholy skull 2") {
            if (monster_type_ == "unholy skull 1") monster_number_ = 2;
            if (monster_type_ == "unholy skull 2") monster_number_ = 3;
            monster_hp_ = monster_full_hp_ = 12;
            monster_dmg_ = 4;
            monster_exp_drop_ = 1;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/UnholySkullIdleSide.png");   
        }
        else if (monster_type_ == "virulent wight 1" || monster_type_ == "virulent wight 2") {
            if (monster_type_ == "virulent wight 1") monster_number_ = 0;
            if (monster_type_ == "virulent wight 2") monster_number_ = 5;
            monster_hp_ = monster_full_hp_ = 15;
            monster_dmg_ = 6;
            monster_exp_drop_ = 2;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/VirulentWightIdleSide.png");   
        }
        else if (monster_type_ == "ocular watcher") {
            monster_hp_ = monster_full_hp_ = 1;
            monster_dmg_ = 5;
            monster_exp_drop_ = 1;
            monster_number_ = 2;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/OcularWatcherIdleSide.png");
            monster_sprite_.setTexture(monster_texture_);
            monster_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
        } 
        else if (monster_type_ == "bloodshot eye") {
            monster_hp_ = monster_full_hp_ = 1;
            monster_dmg_ = 4;
            monster_exp_drop_ = 1;
            monster_number_ = 1;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/BloodshotEyeIdleSide.png");
            monster_sprite_.setTexture(monster_texture_);
            monster_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
            
        }
        else if (monster_type_ == "BOSS") {
            monster_hp_ = monster_full_hp_ = 167;
            monster_dmg_ = 8;
            monster_exp_drop_ = 1;
            monster_number_ = 8;

            monster_position_x_ = 0;
            monster_position_y_ = 0;

            //Parte das texturas e animações
            number_of_frames_ = 9;
            monster_texture_.loadFromFile("Textures/GrandmasterWarlockIdle.png");
        }
    monster_sprite_.setTexture(monster_texture_);
}

    // obs.: template só foi usado devido a um erro de reconhecimento de um tipo pelo compilador. Essa foi
    // a única forma que funcionou
    template <typename T>
    void Monster::set_monster_hp(Board* my_game_board,  std::vector<std::unique_ptr<T>>& items_, int dmg) {
        monster_hp_ -= dmg;
          if (monster_hp_ <= 0) {
            monster_hp_ = 0;
            my_game_board->get_tile_at(monster_position_x_, monster_position_y_)->deleteObjectInTile();
            Item* new_item = std::unique_ptr<Item> (new Item(monster_position_x_, monster_position_y_));
            items_.push_back(new_item);
            if (new_item->get_item_type() != "empty") {
                my_game_board->get_tile_at(monster_position_x_, monster_position_y_)->setObjectInTile("item");
            }

          }
          else if (monster_hp_ >= monster_full_hp_) {
            monster_hp_ = monster_full_hp_;
        }
    }

    template <>
    void Monster::set_monster_hp(Board* my_game_board, std::vector<std::unique_ptr<Item>>& items_, int dmg) {
        monster_hp_ -= dmg;
          if (monster_hp_ <= 0) {
            monster_hp_ = 0;
            my_game_board->get_tile_at(monster_position_x_, monster_position_y_)->deleteObjectInTile();
            items_.push_back(std::unique_ptr<Item> (new Item(monster_position_x_, monster_position_y_)));
          }
          else if (monster_hp_ >= monster_full_hp_) {
            monster_hp_ = monster_full_hp_;
          }
    }
  
    int Monster::get_monster_full_hp() {
        return monster_full_hp_;
    }

    int Monster::get_monster_hp() {
        return monster_hp_;
    }

    bool Monster::monsterIsDead() {
        if (monster_hp_ > 0) return false;
        else return true;
    }

    int Monster::get_exp_drop() {
        return monster_exp_drop_;
    }

    int Monster::get_dmg_output() {
        return monster_dmg_;
    }

    int Monster::get_monster_number() {
        return monster_number_;
    }

    int Monster::get_monster_position_x() {
        return monster_position_x_;
    }

     int Monster::get_monster_position_y() {
        return monster_position_y_;
    }

    void Monster::set_monster_position_x(int xi) {
        monster_position_x_ = xi;
    }
 
    void Monster::set_monster_position_y(int yi) {
        monster_position_y_ = yi;
    }

    sf::Texture& Monster::get_monster_texture() {
        return monster_texture_;
    }

    sf::Sprite& Monster::get_monster_sprite() {
        return monster_sprite_;
    }

    void Monster::set_monster_sprite(sf::Sprite& defined_sprite) {
        monster_sprite_ = defined_sprite;
    }

    void Monster::updateAnimation(float delta_time) {
        float animation_interval = 0.5f;
        animation_timer_ += delta_time;

        if (animation_timer_ > animation_interval) {
            current_frame_ = (current_frame_ + 1)%number_of_frames_;

            int frame_width = monster_texture_.getSize().x / number_of_frames_;
            int frame_height = monster_texture_.getSize().y;
            monster_sprite_.setTextureRect(sf::IntRect(current_frame_ * frame_width, 0, frame_width, frame_height));

            animation_timer_ = 0.0f;
        }
    }
    Monster::~Monster() {}
    