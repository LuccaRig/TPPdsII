#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include <vector>

class Board{
  public:

    //Exemplo para acessar o estado de um Tile: MyBoard[1][2].Hero_IsInTile -> checa se o quadrado tem um heroi 

    /// @brief Constructor: Cria o tabuleiro e cria os Tiles como vazios inicialmente
    Board();

    /// @brief Destructor
    ~Board();

    /// @brief Coloca um heroi no tabuleiro PRECONDIÇÃO:lugar que esteja vazio
    void heroPutInBoard(std::string hero_type, int linha, int coluna);

    /// @brief Move o heroi no tabuleiro PRECONDIÇÃO:lugar que esteja vazio
    void heroMoveInBoard(std::string hero_type, int linha, int coluna);

    /// @brief Coloca um monstro no tabuleiro PRECONDIÇÃO:lugar que esteja vazio
    void monsterPutInBoard(std::string monster_type, int linha, int coluna);

    /// @brief Move um monstro no tabuleiro em direção o heroi mais "proximo"
    void monsterMoveInBoard(std::string monster_type);

    /// @brief Coloca um item no tabuleiro PRECONDIÇÃO:lugar que esteja vazio 
    void itemPutInBoard(std::string item_type, int linha, int coluna);

    /// @brief Checa se ainda existe algum inimigo no tabuleiro
    bool hordeIsDefeted();

    /// @brief acha um heroi no tabuleiro para o monstro seguir
    /// @return retona as cordenadas no tabuleiro que está o heroi
    std::vector<int> findHeroPosition();

    /// @return Retorna o estado de algum Tile em uma posição específica 
    Tile* getTileAt(int selected_line, int selected_column);

  private:

    /// @brief Matriz que armazena os Tiles, cada Tile tem um conteúdo para distinguir
    /// qual objeto está em cima dele
    std::vector<std::vector<Tile*>> MyBoard;
};

#endif