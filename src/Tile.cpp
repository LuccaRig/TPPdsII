#include "Tile.h"

#include <iostream>

Tile::Tile(){
    content_ = "vazio";
    tile_size_ = 80;
    tile_border_size_ = 5; 
}

Tile::~Tile()
{
}

void Tile::setObjectInTile(std::string content)
{
    content_ = content;
}

void Tile::deleteObjectInTile()
{
    content_ = "vazio";
}

std::string Tile::getObjectInTile()
{
    return content_;
}

int Tile::getTileSize(){
    return this->tile_size_;
}

int Tile::getTileBorderSize(){
    return this->tile_border_size_;

}

bool Tile::isEmpty()
{
    if (content_ == "vazio") return true;
    return false;
}

bool Tile::heroIsInTile()
{
    if (content_ == "hero") return true;
    return false;
}

bool Tile::monsterIsInTile()
{
    if (content_ == "monster") return true;
    return false;
}

bool Tile::itemIsInTile()
{
    if (content_ == "item") return true;
    return false;
}

bool Tile::moveableTile()
{
    if (content_ == "hero" || content_ == "monster") return false;
    return true;
}