#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include <iostream>

#include "Tile.h"

class Board{
  public:

    
    /// TODO: criar um função que tira do tabuleiro heróis e monstros que foram mortos. A função só vai ser chamada se eles estiverem 
    // mortos, então não precisa testar isso. Vale lembrar que algo tem que ser feito em relação ao drop de itens dos monstros nessa função
    /// TODO: monsterMoveInBoard não deve precisar de parâmetros de posição para onde mover, a própria função deve descobrir o melhor lugar
    // para onde o monstro vai se mover.

    //Exemplo para acessar o estado de um Tile: MyBoard[1][2].Hero_IsInTile -> checa se o quadrado tem um heroi 

    /// @brief Constructor: Cria o tabuleiro e cria os Tiles como vazios inicialmente
    Board();

    /// @brief Destructor
    ~Board();

    /// @brief Coloca um heroi no tabuleiro PRECONDIÇÃO:lugar que esteja vazio
    void heroPutInBoard(std::string hero_type, int linha, int coluna);

    /// @brief Move o heroi no tabuleiro PRECONDIÇÃO:lugar que esteja vazio
    void heroMoveInBoard(std::string hero_type, int linha, int coluna);

    /// @param monster_type_code Esse é o tipo e o número do monstro para diferenciarmos diferentes monstros
    /// e suas posições no tabuleiro 
    /// @brief Coloca um monstro no tabuleiro PRECONDIÇÃO:lugar que esteja vazio
    void monsterPutInBoard(std::string monster_type_code, int linha, int coluna);

    /// @param monster_type_code Esse é o tipo e o número do monstro para diferenciarmos diferentes monstros
    /// e suas posições no tabuleiro
    /// @param hero_position Esse valor é o local para onde o monstro deve se mover, esse valor é encontrado
    /// por meio da função findHeroPosition() 
    /// @brief Move um monstro no tabuleiro PRECONDIÇÃO: lugar que esteja vazio e não fora do tabuleiro
    void monsterMoveInBoard(std::string monster_type_code, std::vector<int> hero_position);

    /// @brief Coloca um item no tabuleiro PRECONDIÇÃO:lugar que esteja vazio 
    void itemPutInBoard(std::string item_type, int linha, int coluna);

    /// @brief Checa se ainda existe algum inimigo no tabuleiro
    bool hordeIsDefeted();

    /// @brief acha um heroi no tabuleiro para o monstro seguir
    /// @return retona as cordenadas no tabuleiro que está o heroi
    std::vector<int> findHeroPosition(); 

  private:

    /// @brief Matriz que armazena os Tiles, cada Tile tem um conteúdo para distinguir
    /// qual objeto está em cima dele
    std::vector<std::vector<Tile>> MyBoard[5][5];
};

#endif // BOARD_H_
