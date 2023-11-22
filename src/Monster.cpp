#include <string>

#include "Monster.h"
#include "Board.h"
#include "Item.h"
#include "Hero.h"


    Monster::Monster (std::string monster_type) {
        monster_type_ = monster_type;
        monster_sprite_ = sf::Sprite();

        number_of_frames_ = 4;
        current_frame_ = 0;
        animation_timer_ = 0.0f;

        if (monster_type_ == "bloody abomination") {
            monster_hp_ = 12;
            monster_dmg_ = 8;
            monster_exp_drop_ = 5;

            monster_position_x_ = 0;
            monster_position_y_ = 0;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/BloodyAbominationIdleSide.png");
            monster_sprite_.setTexture(monster_texture_);
            monster_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
        }
        else if (monster_type_ == "death knight") {
             monster_hp_ = 20;
            monster_dmg_ = 6;
            monster_exp_drop_ = 8;

            monster_position_x_ = 0;
            monster_position_y_ = 0;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/DeathKnightIdleSide.png");
            monster_sprite_.setTexture(monster_texture_);
            monster_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
        }
        else if (monster_type_ == "sand golem") {
            monster_hp_ = 40;
            monster_dmg_ = 2;
            monster_exp_drop_ = 1;

            monster_position_x_ = 0;
            monster_position_y_ = 0;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/SandGolemIdleSide.png");
            monster_sprite_.setTexture(monster_texture_);
            monster_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
        }
        else if (monster_type_ == "ghastly beholder") {
            monster_hp_ = 10;
            monster_dmg_ = 2;
            monster_exp_drop_ = 1;

            monster_position_x_ = 0;
            monster_position_y_ = 0;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/GhastlyBeholderIdleSide.png");
            monster_sprite_.setTexture(monster_texture_);
            monster_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
        }
        else if (monster_type_ == "unholy skull") {
            monster_hp_ = 10;
            monster_dmg_ = 4;
            monster_exp_drop_ = 1;

            monster_position_x_ = 2;
            monster_position_y_ = 0;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/UnholySkullIdleSide.png");
            monster_sprite_.setTexture(monster_texture_);
            monster_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
        }
        else if (monster_type_ == "virulent wight") {
            monster_hp_ = 13;
            monster_dmg_ = 5;
            monster_exp_drop_ = 1;

            monster_position_x_ = 0;
            monster_position_y_ = 0;

            //Parte das texturas e animações
            monster_texture_.loadFromFile("Textures/VirulentWightIdleSide.png");
            monster_sprite_.setTexture(monster_texture_);
            monster_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
        }
}

    void Monster::set_monster_hp(int dmg) {
        monster_hp_ -= dmg;
          if (monster_hp_ <= 0) {
            //Item m_item(monster_position_x_, monster_position_y_);
            // Board::registerItem(m_item);
            this->~Monster();
          }
    }

    bool Monster::monsterIsDead() {
        if (monster_hp_ > 0) {
            return false;
        } else {
            return true;
        }
    }

    int Monster::get_exp_drop() {
        return monster_exp_drop_;
    }

    int Monster::get_dmg_output() {
        return monster_dmg_;
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
    Monster::~Monster() {    
    }