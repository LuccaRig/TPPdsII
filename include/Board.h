#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

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

    /// @brief Coloca um heroi no tabuleiro PRECONDIÇÃO:lugar que esteja vazio TODO: classe Hero
    void HeroPutInBoard(/*Hero myHero*/ int linha, int coluna);

    /// @brief Move o heroi no tabuleiro PRECONDIÇÃO:lugar que esteja vazio TODO: classe Hero
    void HeroMoveInBoard(/*Hero myHero*/ int linha, int coluna);

    /// @brief Coloca um monstro no tabuleiro PRECONDIÇÃO:lugar que esteja vazio TODO: classe Monster
    void MonsterPutInBoard(/*Monster myMonster*/ int linha, int coluna);

    /// @brief Move um monstro no tabuleiro PRECONDIÇÃO:lugar que esteja vazio TODO: classe Monster
    void MonsterMoveInBoard(/*Monster myMonster*/ int linha, int coluna);

    /// @brief Coloca um item no tabuleiro PRECONDIÇÃO:lugar que esteja vazio TODO: classe Item
    void ItemPutInBoard(/*Item itemDropped*/ int linha, int coluna);

    /// @brief Checa se ainda existe algum inimigo no tabuleiro
    bool HordeIsDefeted();
};

#endif