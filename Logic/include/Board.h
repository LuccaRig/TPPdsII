#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include <vector>

class Board{
private:

    /// @brief Matriz que armazena os Tiles no tabuleiro, linha/coluna
    std::vector<std::vector<Tile>> MyBoard[5][5];

public:

    //Exemplo para acessar o estado de um Tile: MyBoard[1][2].Hero_IsInTile -> checa se o quadrado tem um heroi 

    /// @brief Constructor: Cria o tabuleiro e cria os Tiles como vazios inicialmente
    Board();

    /// @brief Destructor
    ~Board();

    /// @brief Coloca um heroi no tabuleiro PRECONDIÇÃO:lugar que esteja vazio
    void heroPutInBoard(std::string Hero, int linha, int coluna);

    /// @brief Move o heroi no tabuleiro PRECONDIÇÃO:lugar que esteja vazio
    void heroMoveInBoard(std::string Hero, int linha, int coluna);

    /// @brief Coloca um monstro no tabuleiro PRECONDIÇÃO:lugar que esteja vazio
    void monsterPutInBoard(std::string Hero, int linha, int coluna);

    /// @brief Move um monstro no tabuleiro PRECONDIÇÃO:lugar que esteja vazio
    void monsterMoveInBoard(std::string MonsterType, int linha, int coluna);

    /// @brief Coloca um item no tabuleiro PRECONDIÇÃO:lugar que esteja vazio
    void itemPutInBoard(std::string Item, int linha, int coluna);

    /// @brief Checa se ainda existe algum inimigo no tabuleiro
    bool hordeIsDefeted();
};

#endif