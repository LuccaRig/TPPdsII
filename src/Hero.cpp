#include "Hero.h"

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


Hero::Hero(std::string hero_type) {
    current_exp_ = 0;
    needed_exp_ = 2;
    hero_lvl_ = 1;
    hero_type_ = hero_type;
    hero_sprite_ = sf::Sprite();
    
    number_of_frames_ = 4;
    current_frame_ = 0;
    animation_timer_ = 0.0f;

    if (hero_type_ == "knight") {
        hero_hp_ = hero_full_hp_ = 35;
        hero_attack_ = 20;
        hero_special_attack_ = 4;
        hero_number_ = 0;
        skill_cooldown_ = 2;
        
        hero_position_x_ = 2;
        hero_position_y_ = 2;

        //Parte das texturas e animações
        hero_texture_.loadFromFile("Textures/RadiantPaladinIdleSide.png");
        hero_sprite_.setTexture(hero_texture_);
        hero_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
    }
    else if (hero_type_ == "rogue"){
        hero_hp_ = hero_full_hp_ = 25;
        hero_attack_ = 20;
        hero_special_attack_ = 5;
        hero_number_ = 2;
        skill_cooldown_ = 1;

        hero_position_x_ = 3;
        hero_position_y_ = 2;

        //Parte das texturas e animações
        hero_texture_.loadFromFile("Textures/HalflingAssassinIdleSide.png");
        hero_sprite_.setTexture(hero_texture_);
        hero_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
    }
    else if (hero_type_ == "mage") {
        hero_hp_ = hero_full_hp_ = 30;
        hero_attack_ = 20;
        hero_special_attack_ = 15;
        hero_number_ = 1;
        skill_cooldown_ = 2;
        
        hero_position_x_ = 1;
        hero_position_y_ = 2;

        //Parte das texturas e animações
        hero_texture_.loadFromFile("Textures/NovicePyromancerIdle.png");
        hero_sprite_.setTexture(hero_texture_);
        hero_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
    }

}

bool Hero::isAlive() {
    if(hero_hp_ <= 0){
        return false;
    }
    else{
        return true;
    }
}

int Hero::get_hero_full_hp() {
    return hero_full_hp_;
}

int Hero::get_hero_hp() {
    return hero_hp_;
}

void Hero::set_hero_hp(int changed_hp) {
    hero_hp_ -= changed_hp;
    if (hero_hp_ <= 0) {
        hero_hp_ = 0;
        hero_position_x_ = 60;
        hero_position_y_ = 60;
    }
    else if (hero_hp_ >= hero_full_hp_) {
        hero_hp_ = hero_full_hp_;
    }
}

int Hero::get_hero_attack() {
    return hero_attack_;
}

void Hero::set_hero_attack(int changed_attack) {
    hero_attack_ += changed_attack;
}

int Hero::get_hero_special_attack() {
    return hero_special_attack_;
}

void Hero::set_hero_special_attack(int change) {
    hero_special_attack_ += change;
} 

int Hero::get_skill_cooldown() {
    return skill_cooldown_;
}

void Hero::restartSkillCooldown() {
    skill_cooldown_ = 0;
}

void Hero::decreaseSkillCooldown() {
    skill_cooldown_++;
}

void Hero::set_current_exp(int monster_exp, std::string hero_type) {
  current_exp_ += monster_exp;
  if (current_exp_ >= needed_exp_) {
    current_exp_ -= needed_exp_;
    lvlUp(hero_type);
  }
}

void Hero::lvlUp(std::string hero_type) {
    hero_lvl_++;
    if (hero_type == "knight") {
        hero_hp_ += 5;
        hero_full_hp_ += 5;
        hero_attack_ += 1;
        hero_special_attack_ += 2;
        needed_exp_ += 2;
    }
    else if (hero_type == "rogue") {
        hero_hp_ += 2;
        hero_full_hp_ += 2;
        hero_attack_ += 3;
        hero_special_attack_ += 1;
        needed_exp_ += 2;
    }
    else if (hero_type == "mage") {
        hero_hp_ += 2;
        hero_full_hp_ += 2;
        hero_attack_ += 1;
        hero_special_attack_ += 2;
        needed_exp_ += 2;
    }
}

int Hero::get_hero_lvl() {
    return hero_lvl_;
}

std::string Hero::get_hero_type() {
    return hero_type_;
}

int Hero::get_hero_number() {
    return hero_number_;
}

int Hero::get_hero_position_x() {
    return hero_position_x_;
}

void Hero::set_hero_position_x(int current_position) {
    hero_position_x_ = current_position;
}

int Hero::get_hero_position_y() {
    return hero_position_y_;
}

void Hero::set_hero_position_y(int current_position) {
    hero_position_y_ = current_position;
}

sf::Texture Hero::get_hero_texture() {
    return hero_texture_;
}

sf::Sprite& Hero::get_hero_sprite() {
    return hero_sprite_;
}

void Hero::set_hero_sprite(sf::Sprite defined_sprite) {
    hero_sprite_ = defined_sprite;
}

void Hero::updateAnimation(float delta_time) {
    float animation_interval = 0.5f;
    animation_timer_ += delta_time;

    if(animation_timer_ > animation_interval) {
        current_frame_ = (current_frame_ + 1)%number_of_frames_;

        int frame_width = hero_texture_.getSize().x / number_of_frames_;
        int frame_height = hero_texture_.getSize().y;
        hero_sprite_.setTextureRect(sf::IntRect(current_frame_ * frame_width, 0, frame_width, frame_height));

        animation_timer_ = 0.0f;
    }
}

Hero::~Hero() {

}