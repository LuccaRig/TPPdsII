#include "Board.h"

#include <vector>
#include <iostream>

Board::Board() {
   my_board_.resize(5, std::vector<Tile*>(5, nullptr));
    for (int i = 0;i < 5;i++) {
        for (int j = 0;j < 5;j++) {
           my_board_[i][j] = new Tile();
        }
    }
}

Board::~Board(){
    for (int i = 0;i < 5;i++) {
        for (int j = 0;j < 5;j++) {
            delete my_board_[i][j];
        }
    }
}

Tile* Board::get_tile_at(int selected_line, int selected_column) {
    if ((selected_line >= 0) && (selected_line < 5) && (selected_column >= 0) && (selected_column < 5)) {
        return my_board_[selected_line][selected_column];
    }
    //Caso um valor fora do Board tenha sido selecionado:
    return nullptr;
}