#ifndef MONSTER_H_
#define MONSTER_H_

#include <string>
#include <vector>

#include "Item.h"
#include "Board.h"
#include "Tile.h"
#include "Hero.h"

class Monster {
  
  public:

    /// @brief contrói monstros com diferentes características dependendo do tipo de monstro recebido
    Monster(std::string monster_type);

    /// @brief destrutor
    ~Monster();

    /// @brief Retorna o hp máximo do monstro
    int get_monster_full_hp();

    /// @brief Retorna o hp atual do monstro
    int get_monster_hp();

    /// @brief  subtrai o valor recebido em pontos de vida para o monstro e checa se o monstro foi derrotado
    /// para, caso sim, um item seja criado para aparecer na coordenada do monstro
    /// @param  attack_ do herói
    /// @param items_ vetor de itens onde o item será criado
    template<typename T>
    void set_monster_hp(Board* my_game_board, std::vector<std::unique_ptr<T>>& items_, int dmg);

    /// @return retorna true se o monstro estiver morto e false se não estiver.
    bool monsterIsDead();

    /// @return retorna o número de experiência que o monstro dará quando for derrotado
    int get_exp_drop();

    /// @return retorna a quantidade de dano que o monstro aplica
    int get_dmg_output();

    /// @return retorna o número relativo ao monstro
    int get_monster_number();

    /// @return retorna a coordenada x do monstro
    int get_monster_position_x();

    /// @return retorna a coordenada y do monstro
    int get_monster_position_y();

    /// @brief substitui a coordenada x do monstro pra xi
    void set_monster_position_x(int xi);

    /// @brief substitui a coordenada y do monstro pra yi
    void set_monster_position_y(int yi);

    /// @return Textura do monstro/SpriteSheet
    sf::Texture& get_monster_texture();

    /// @return Corte específico da SpriteSheet do monstro(Sprite)
    sf::Sprite& get_monster_sprite();

    /// @brief Define um corte ou sprite específico do monstro
    void set_monster_sprite(sf::Sprite& defined_sprite);

    /// @brief atualiza o sprite do monstro 
    /// @param deltaTime 
    void updateAnimation(float deltaTime);

  private:
    //Características
    std::string monster_type_;
    int monster_full_hp_;
    int monster_hp_;
    int monster_dmg_;
    int monster_exp_drop_;
    int monster_number_;

    int monster_position_x_;
    int monster_position_y_;

    //Animações
    sf::Texture monster_texture_;
    sf::Sprite monster_sprite_;

    int number_of_frames_;
    int current_frame_;
    float animation_timer_;

};

#endif // MONSTER_H_