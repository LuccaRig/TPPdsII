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
    bool IsEmpty();

    /// @brief Checa se o quadrado tem um heroi
    bool Hero_IsInTile();

    /// @brief Checa se o quadrado tem um monstro
    bool Monster_IsInTile();

    /// @brief Checa se o quadrado tem um item
    bool Item_IsInTile();

};

#endif

