#include "Board.h"

Board::Board() {
    MyBoard.resize(5, std::vector<Tile*>(5, nullptr));
    for (int i = 0;i < 5;i++) {
        for (int j = 0;j < 5;j++) {
            MyBoard[i][j] = new Tile();
        }
    }
}

Board::~Board(){
    for (int i = 0;i < 5;i++) {
        for (int j = 0;j < 5;j++) {
            delete MyBoard[i][j];
        }
    }
}

void Board::heroPutInBoard(std::string Hero, int linha, int coluna)
{
}

void Board::heroMoveInBoard(std::string Hero, int linha, int coluna)
{
}

void Board::monsterPutInBoard(std::string Hero, int linha, int coluna)
{
}

void Board::monsterMoveInBoard(std::string MonsterType, std::vector<int> hero_position)
{
}

void Board::itemPutInBoard(std::string Item, int linha, int coluna)
{
}

bool Board::hordeIsDefeted()
{
    return false;
}

std::vector<int> Board::findHeroPosition()
{
    return std::vector<int>();
}

Tile* Board::getTileAt(int selected_line, int selected_column) {
    if ((selected_line >= 0) && (selected_line < 5) && (selected_column >= 0) && (selected_column < 5)) {
        return MyBoard[selected_line][selected_column];
    }
    //Caso um valor fora do Board tenha sido selecionado:
    return nullptr;
}