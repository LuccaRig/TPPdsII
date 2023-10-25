#ifndef TILE_H
#define TILE_H

#include <iostream>

class Tile{
private:
    std::string Content_;

public:

    /// @brief Constructor
    Tile(std::string Objectflag);

    /// @brief Destructor
    ~Tile();

    /// @brief Checa se o quadrado está vazio
    bool isEmpty();

    /// @brief Checa se o quadrado tem um heroi
    bool hero_IsInTile();

    /// @brief Checa se o quadrado tem um monstro
    bool monster_IsInTile();

    /// @brief Checa se o quadrado tem um item
    bool item_IsInTile();

};

#endif

