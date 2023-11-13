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

    if (hero_type_ == "knight") {
        hero_hp_ = 25;
        hero_attack_ = 7;
        hero_special_attack_ = 5;
        
        //Parte das texturas e animações
        hero_texture_.loadFromFile("Textures/SkilledBattlemageIdle.png");
        hero_sprite_.setTexture(hero_texture_);
        hero_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
    }
    else if (hero_type_ == "rogue"){
        hero_hp_ = 10;
        hero_attack_ = 12;
        hero_special_attack_ = 5;
    }
    else if (hero_type_ == "mage"){
        hero_hp_ = 15;
        hero_attack_ = 5;
        hero_special_attack_ = 15;
        
        //Parte das texturas e animações
        hero_texture_.loadFromFile("Textures/GrandmasterWarlockIdle.png");
        hero_sprite_.setTexture(hero_texture_);
        hero_sprite_.setTextureRect(sf::IntRect(0, 0, 32, 32));
    }

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