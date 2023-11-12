#include "Tile.h"

#include <iostream>

Tile::Tile(){
    this->content_ = "vazio";
    this->tile_size_ = 80;
    this->tile_border_size_ = 5; 
}

Tile::~Tile()
{
}

void Tile::setObjectInTile()
{
}

void Tile::getObjectInTile()
{
}

int Tile::getTileSize(){
    return this->tile_size_;
}

int Tile::getTileBorderSize(){
    return this->tile_border_size_;

}

bool Tile::isEmpty()
{
    return false;
}

bool Tile::heroIsInTile()
{
    return false;
}

bool Tile::monsterIsInTile()
{
    return false;
}

bool Tile::itemIsInTile()
{
    return false;
}
