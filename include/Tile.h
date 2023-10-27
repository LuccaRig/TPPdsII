#ifndef TILE_H
#define TILE_H

#include <iostream>

class Tile{
  public:

    /// @brief Constructor, Tile inicializado como vazio sempre
    Tile();

    /// @brief Destructor
    ~Tile();

    /// @brief Modifica o valor do conteúdo do Tile
    void setObjectInTile();

    /// @brief Retorna qual o conteúdo do Tile Atuala 
    void getObjectInTile();

    /// @brief Retorna o tamanho do lado do Tile
    int getTileSize();

    /// @brief Retorna o tamanho da borda do Tile
    int getTileBorderSize();

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
    int tile_size_;
    int tile_border_size_;
};

#endif
