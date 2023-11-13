#ifndef ITEM_H_
#define ITEM_H_

#include <string>
#include <vector>
#include <map>

#include "Monster.h"

using std::string;

class Item {
    
  public:

    /// @brief constructor, constrói um item com posição e tipo definidos
    Item(int x, int y);

    /// @returns retorna um tipo de item ou uma string vazia significando nenhum item. Os itens serão
    /// construídos e nomeados dentro da própria função 
    string returnsRandomItem();

    int returns_item_position_x();

    int returns_item_position_y();

    string returns_item_type();


  private:
    
    std::string item_type_;
    int item_position_x_;
    int item_position_y_;
    
};

#endif // ITEM_H_