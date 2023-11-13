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

class Hero{

  public:

    /// @brief Constructor TODO: Atribui os status para cada hero_type_, assim como o spell_type_
    Hero(std::string type);

    /// @brief Destructor
    ~Hero();

    /// @return Retorna o hp do herói
    int get_hero_hp();

    /// @brief Altera o hp atual do herói
    void set_hero_hp(int changed_hp);

    /// @return Retorna o ataque do herói
    int get_hero_attack();

    /// @return Retorna o ataque especial do herói
    int get_hero_special_attack();

    // /// @brief Move o herói para um número determinado de casas adjacentes
    // void HeroMove();

    // /// @brief Ataca uma das 4 casas adjacentes ao herói
    // void HeroAttack();

    /// @brief Utiliza a habilidade especial do herói
    void UseSkill();

    // /// @brief Utiliza um item dropado por um monstro
    // void UseItem(Item dropped_item);

    // /// @return Retorna o nível do herói
    // int current_lvl(int experience);

    // /// @brief Aumenta o nível do herói
    // void LvlUp(int lvl);

    /// @return Posição x do herói no tabuleiro
    int get_hero_position_x();

    /// @brief Altera a posição x do herói no tabuleiro
    void set_hero_position_x(int current_position);

    /// @return Posição y do herói no tabuleiro
    int get_hero_position_y();

    /// @brief Altera a posição y do herói no tabuleiro
    void set_hero_position_y(int current_position);

    /// @return Textura do heroi/SpriteSheet
    sf::Texture getHeroTexture();

    /// @return Corte específico da SpriteSheet do heroi(Sprite)
    sf::Sprite& getHeroSprite();

    /// @brief Define um corte ou sprite específico do heroi
    void setHeroSprite(sf::Sprite defined_sprite);

    void updateAnimation(sf::Time deltaTime);    

  private:
    //Características
    int hero_hp_;
    int hero_attack_;
    int hero_special_attack_;
    int exp_;
    std::string hero_type_;
  
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