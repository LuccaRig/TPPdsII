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
    item_type_ = returnsRandomItem();
    item_position_x_ = x;
    item_position_y_ = y;
    item_used_ = false;
    
    if (item_type_ == "heal") {
        item_texture_.loadFromFile("Textures/potion_red.png");
        item_sprite_.setTexture(item_texture_);
        item_sprite_.setTextureRect(sf::IntRect(0, 0, 7, 8));
        item_effect_ = 50;
    } else if (item_type_ == "spellBuff") {
        item_texture_.loadFromFile("Textures/potion_blue.png");
        item_sprite_.setTexture(item_texture_);
        item_sprite_.setTextureRect(sf::IntRect(0, 0, 7, 8));
        item_effect_ = 25;
    } else if (item_type_ == "dmgBuff") {
        item_texture_.loadFromFile("Textures/potion_green.png");
        item_sprite_.setTexture(item_texture_);
        item_sprite_.setTextureRect(sf::IntRect(0, 0, 7, 8));
        item_effect_ = 40;
    }
}

std::string Item::returnsRandomItem() {
    std::map<int, std::string> item_n;
    item_n[1] = "heal";
    item_n[2] = "heal";
    item_n[3] = "spellBuff";
    item_n[4] = "dmgBuff";
    // chance final de cair item vai ser 50%
    srand((unsigned) time(NULL));
	int random = 1 + rand()%4;

    if (random <= 4) {
        return item_n[random];
    } else {
        return "empty";
    }
}

bool Item::itemWasUsed() {
    return item_used_;
}

void Item::set_item_to_used() {
    item_used_ = true;
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

sf::Sprite& Item::get_item_sprite() {
  return item_sprite_;
}

int Item::get_item_effect() {
    return item_effect_;
}

Item::~Item() {}
