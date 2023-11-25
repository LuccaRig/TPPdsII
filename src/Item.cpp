#include "Item.h"

#include <string>
#include <vector>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


Item::Item(int x, int y) {
    item_type_ = "heal"; // returnsRandomItem();
    item_position_x_ = x;
    item_position_y_ = y;
    
    if (item_type_ == "heal") {
        item_texture_.loadFromFile("Textures/potion_red.png");
        item_sprite_.setTexture(item_texture_);
        item_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
        item_effect_ = 50;
    } else if (item_type_ == "spellBuff") {
        item_texture_.loadFromFile("Textures/potion_blue.png");
        item_sprite_.setTexture(item_texture_);
        item_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
        item_effect_ = 9;
    } else if (item_type_ == "dmgBuff") {
        item_texture_.loadFromFile("Textures/potion_green.png");
        item_sprite_.setTexture(item_texture_);
        item_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
        item_effect_ = 5;
    }
}

std::string Item::returnsRandomItem() {
    std::map<int, std::string> item_n;
    item_n[1] = "heal";
    item_n[2] = "heal";
    item_n[3] = "heal";
    item_n[4] = "heal";

    srand((unsigned) time(NULL));
	int random = 1 + rand()%5;

    if (random <= 4) {
        return item_n[random];
    } else {
        return "empty";
    }
}

int Item::get_item_position_x() {
    return item_position_x_;
}

int Item::get_item_position_y() {
    return item_position_y_;
}

std::string Item::get_item_type() {
  return item_type_;
}

sf::Sprite Item::get_item_sprite() {
  return item_sprite_;
}

int Item::get_item_effect() {
    return item_effect_;
}

