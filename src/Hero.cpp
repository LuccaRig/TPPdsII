#include "Hero.h"

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


Hero::Hero(std::string type){
    exp_ = 0;
    hero_type_ = type;
    hero_sprite_ = sf::Sprite();
    
    number_of_frames_ = 4;
    current_frame_ = 0;
    animation_timer_ = 0.0f;

    if (hero_type_ == "knight") {
        hero_hp_ = 35;
        hero_attack_ = 5;
        hero_special_attack_ = 5;
        
        //Parte das texturas e animações
        hero_texture_.loadFromFile("Textures/RadiantPaladinIdleSide.png");
        hero_sprite_.setTexture(hero_texture_);
        hero_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
    }
    else if (hero_type_ == "rogue"){
        hero_hp_ = 25;
        hero_attack_ = 10;
        hero_special_attack_ = 1;

        //Parte das texturas e animações
        hero_texture_.loadFromFile("Textures/HalflingAssassinIdleSide.png");
        hero_sprite_.setTexture(hero_texture_);
        hero_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
    }
    else if (hero_type_ == "mage"){
        hero_hp_ = 30;
        hero_attack_ = 4;
        hero_special_attack_ = 15;
        
        //Parte das texturas e animações
        hero_texture_.loadFromFile("Textures/NovicePyromancerIdle.png");
        hero_sprite_.setTexture(hero_texture_);
        hero_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
    }

}

int Hero::get_hero_hp(){
    return hero_hp_;
}

void Hero::set_hero_hp(int changed_hp){
    hero_hp_ - changed_hp;
}

int Hero::get_hero_attack(){
    return hero_attack_;
}

int Hero::get_hero_special_attack(){
    return hero_special_attack_;
}

void Hero::UseSkill(){
    Skill skill(hero_type_, hero_special_attack_);
    hero_hp_ += skill.skill_heal();
    hero_attack_ += skill.skill_buff();
    
}

Hero::~Hero(){

}

sf::Texture Hero::getHeroTexture(){
    return hero_texture_;
}

sf::Sprite& Hero::getHeroSprite(){
    return hero_sprite_;
}

void Hero::setHeroSprite(sf::Sprite defined_sprite){
    hero_sprite_ = defined_sprite;
}

void Hero::updateAnimation(sf::Time delta_time){
    float animation_interval = 0.5f;
    animation_timer_ += delta_time.asSeconds();

    if(animation_timer_ > animation_interval){
        current_frame_ = (current_frame_ + 1)%number_of_frames_;

        int frame_width = hero_texture_.getSize().x / number_of_frames_;
        int frame_height = hero_texture_.getSize().y;
        hero_sprite_.setTextureRect(sf::IntRect(current_frame_ * frame_width, 0, frame_width, frame_height));

        animation_timer_ = 0.0f;
    }
}