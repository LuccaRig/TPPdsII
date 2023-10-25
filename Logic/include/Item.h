#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>


class Item {
    
  public:

    /// @brief constructor, constrói um item aleatório.
    Item();

    /// @returns retorna um tipo de item ou uma string vazia significando nenhum item. Os itens serão
    /// construídos e nomeados dentro da própria função 
    std::string returns_random_item;

  private:
    
    std::string item_type_;
    
};

#endif