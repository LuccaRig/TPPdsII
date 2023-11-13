#ifndef ITEM_H_
#define ITEM_H_

#include <string>
#include <vector>
#include <map>

#include "Monster.h"


class Item {
    
  public:

    /// @brief constructor, constrói um item com posição e tipo definidos
    Item(int x, int y);

    /// @returns retorna um tipo de item ou uma string vazia significando nenhum item. Os itens serão
    /// construídos e nomeados dentro da própria função 
    std::string returnsRandomItem();

  

  private:
    
    std::string item_type_;
    int item_position_x_;
    int item_position_y_;
    
};

#endif // ITEM_H_