#ifndef HERO_H_
#define HERO_H_

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Board.h"
#include "Skill.h"
//#include "Item.h"

class Hero {

  public:

    /// @brief Constructor TODO: Atribui os status para cada hero_type_, assim como o spell_type_
    Hero(std::string hero_type);

    /// @brief Destructor
    ~Hero();

    /// @return Retorna o hp máximo do herói
    int get_hero_full_hp();

    /// @return Retorna o hp atual do herói
    int get_hero_hp();

    /// @brief Altera o hp atual do herói
    void set_hero_hp(int changed_hp);

    /// @return Retorna o ataque do herói
    int get_hero_attack();

    /// @brief Altera o dano atual do herói
    void set_hero_attack(int changed_attack);

    /// @return Retorna o ataque especial do herói
    int get_hero_special_attack();

    // /// @brief Utiliza um item dropado por um monstro
    // void UseItem(Item dropped_item);

    /// @brief Altera a experiência atual do herói
    void set_current_exp(int monster_exp, std::string hero_type);

    /// @brief Aumenta o nível do herói
    void lvlUp(std::string hero_type);

    /// @return Retorna o nível atual do herói
    int get_hero_lvl();

    /// @return Retorna a string com o tipo do herói
    std::string get_hero_type();

    /// @return Retorna o número do herói
    int get_hero_number();
    
    /// @return Retorna 1 se o herói estiver vivo
    bool isAlive();

    /// @return Posição x do herói no tabuleiro
    int get_hero_position_x();

    /// @brief Altera a posição x do herói no tabuleiro
    void set_hero_position_x(int current_position);

    /// @return Posição y do herói no tabuleiro
    int get_hero_position_y();

    /// @brief Altera a posição y do herói no tabuleiro
    void set_hero_position_y(int current_position);

    /// @return Textura do heroi/SpriteSheet
    sf::Texture get_hero_texture();

    /// @return Corte específico da SpriteSheet do heroi(Sprite)
    sf::Sprite& get_hero_sprite();

    /// @brief Define um corte ou sprite específico do heroi
    void set_hero_sprite(sf::Sprite defined_sprite);

    void updateAnimation(float deltaTime);    

  private:
    //Características
    int hero_full_hp_;
    int hero_hp_;
    int hero_attack_;
    int hero_special_attack_;
    int current_exp_;
    int needed_exp_;
    int hero_lvl_;
    std::string hero_type_;
    int hero_number_;
  
    int hero_position_x_;
    int hero_position_y_;

    //Animações
    sf::Texture hero_texture_;
    sf::Sprite hero_sprite_;

    int number_of_frames_;
    int current_frame_;
    float animation_timer_;

};

#endif // HERO_H_