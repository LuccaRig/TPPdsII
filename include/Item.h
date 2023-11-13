#ifndef ITEM_H_
#define ITEM_H_

#include <string>
#include <vector>
#include <map>


class Item {
    
  public:

    /// @brief constructor, constrói um item aleatório.
    Item();

    /// @returns retorna um tipo de item ou uma string vazia significando nenhum item. Os itens serão
    /// construídos e nomeados dentro da própria função 
    std::string returnsRandomItem();

  private:
    
    std::string item_type_;
    
};

#endif // ITEM_H_