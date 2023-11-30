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

        if (monster_type_ == "bloody abomination") {
            monster_hp_ = monster_full_hp_ = 12;
            monster_dmg_ = 8;
            monster_exp_drop_ = 1;
            monster_number_ = 4;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/BloodyAbominationIdleSide.png");
            monster_sprite_.setTexture(monster_texture_);
            monster_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
        }
        else if (monster_type_ == "death knight") {
            monster_hp_ = monster_full_hp_ = 20;
            monster_dmg_ = 6;
            monster_exp_drop_ = 1;
            monster_number_ = 5;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/DeathKnightIdleSide.png");
            monster_sprite_.setTexture(monster_texture_);
            monster_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
        }
        else if (monster_type_ == "sand golem") {
            monster_hp_ = monster_full_hp_ = 40;
            monster_dmg_ = 2;
            monster_exp_drop_ = 1;
            monster_number_ = 2;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/SandGolemIdleSide.png");
            monster_sprite_.setTexture(monster_texture_);
            monster_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
        }
        else if (monster_type_ == "ghastly beholder") {
            monster_hp_ = monster_full_hp_ = 10;
            monster_dmg_ = 2;
            monster_exp_drop_ = 1;
            monster_number_ = 3;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/GhastlyBeholderIdleSide.png");
            monster_sprite_.setTexture(monster_texture_);
            monster_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
        }
        else if (monster_type_ == "unholy skull") {
            monster_hp_ = monster_full_hp_ = 10;
            monster_dmg_ = 4;
            monster_exp_drop_ = 1;
            monster_number_ = 0;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/UnholySkullIdleSide.png");
            monster_sprite_.setTexture(monster_texture_);
            monster_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
        }
        else if (monster_type_ == "virulent wight") {
            monster_hp_ = monster_full_hp_ = 13;
            monster_dmg_ = 5;
            monster_exp_drop_ = 1;
            monster_number_ = 1;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/VirulentWightIdleSide.png");
            monster_sprite_.setTexture(monster_texture_);
            monster_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
        }

        else if (monster_type_ == "ocular whatcher") {
            monster_hp_ = monster_full_hp_ = 7;
            monster_dmg_ = 3;
            monster_exp_drop_ = 1;
            monster_number_ = 2;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/OcularWatcherIdleSide.png");
            monster_sprite_.setTexture(monster_texture_);
            monster_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
        } 
        else if (monster_type_ == "bloodshot eye") {
            monster_hp_ = monster_full_hp_ = 5;
            monster_dmg_ = 2;
            monster_exp_drop_ = 1;
            monster_number_ = 1;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/BloodshotEyeIdleSide.png");
            monster_sprite_.setTexture(monster_texture_);
            monster_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
        }
        else if (monster_type_ == "BOSS") {
            monster_hp_ = monster_full_hp_ = 100;
            monster_dmg_ = 5;
            monster_exp_drop_ = 1;
            monster_number_ = 8;

            monster_position_x_ = 0;
            monster_position_y_ = 0;

            //Parte das texturas e animações
            number_of_frames_ = 9;
            monster_texture_.loadFromFile("Textures/GrandmasterWarlockIdle.png");
            monster_sprite_.setTexture(monster_texture_);
            monster_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
        }
}

    template <typename T>
    void Monster::set_monster_hp(Board* my_game_board,  std::vector<std::unique_ptr<T>>& items_, int dmg) {
        monster_hp_ -= dmg;
          if (monster_hp_ <= 0) {
            my_game_board->get_tile_at(monster_position_x_, monster_position_y_)->deleteObjectInTile();
            // items_.push_back(std::unique_ptr<Item> (new Item(monster_position_x_, monster_position_y_)));
            // my_game_board->set_number_of_items(1);
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
            // items_.push_back(std::unique_ptr<Item>(new Item(monster_position_x_, monster_position_y_)));
            // my_game_board->set_number_of_items(1);
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
    