#ifndef ITEM_H_
#define ITEM_H_

#include <string>
#include <vector>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Monster.h"

class Item {
    
  public:

    /// @brief constructor, constrói um item com posição e tipo definidos
    Item(int x, int y);

    /// @returns retorna um tipo de item ou uma string vazia significando nenhum item. Os itens serão
    /// construídos e nomeados dentro da própria função 
    std::string returnsRandomItem();

    /// @return retorna verdadeiro se o item já foi coletado e falso se não 
    bool itemWasUsed();

    /// @brief chamada quando o item for usado
    void set_item_to_used();

    /// @return retorna posição x do item
    int get_item_position_x();

    /// @return retorna posição y do item
    int get_item_position_y();

    /// @return retorna tipo do item 
    std::string get_item_type();

    /// @return retorna o sprite do item
    sf::Sprite& get_item_sprite();

    /// @return retorna quantitativamente o efeito do item
    int get_item_effect();

    /// @brief destrutor
    ~Item();


  private:
    
    std::string item_type_;
    int item_position_x_;
    int item_position_y_;
    int item_effect_;
    bool item_used_;

    sf::Texture item_texture_;
    sf::Sprite item_sprite_;
};

#endif // ITEM_H_