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

    /// @return Retorna o estado de algum Tile em uma posição específica 
    Tile* get_tile_at(int selected_line, int selected_column);

  private:

    /// @brief Matriz que armazena os Tiles, cada Tile tem um conteúdo para distinguir
    /// qual objeto está em cima dele
    std::vector<std::vector<Tile*>> my_board_;
};

#endif // BOARD_H_