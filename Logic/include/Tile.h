#ifndef TILE_H
#define TILE_H

#include <iostream>

class Tile{
  public:

    /// @param object_flag flag do objeto que está em cima do Tile quando ele é criado  
    /// @brief Constructor
    Tile(std::string object_flag);

    /// @brief Destructor
    ~Tile();

    /// @brief Modifica o valor do conteúdo do Tile
    void setObjectInTile();

    /// @brief Checa se o quadrado está vazio
    bool isEmpty();

    /// @brief Checa se o quadrado tem um heroi
    bool heroIsInTile();

    /// @brief Checa se o quadrado tem um monstro
    bool monsterIsInTile();

    /// @brief Checa se o quadrado tem um item
    bool itemIsInTile();


  private:
    std::string content_;

};

#endif

