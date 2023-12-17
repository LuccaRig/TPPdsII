#ifndef MAGIC_H
#define MAGIC__H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Magic{
  public:
    /// @brief Constructor
    Magic();

    /// @brief Realiza a animacao da magia de ataque fire_ball_
    /// @param delta_time = tempo decorrido desde o ultimo clock
    void attackMagicAnimation(float delta_time);

    /// @brief getter para o sprite atual da magia
    /// @return uma referencia para o sprite atual da magia
    sf::Sprite& get_magic_sprite();

    /// @brief define que a animacao da magia acabou
    void finishMagicAnimation();

    /// @brief reinicia os frames da magia para ser utilizada de novo
    void set_frame_zero();

    /// @brief define que a animacao comecou fazendo com que o magic_animation_is_finished_
    /// seja falso
    void magicAnimationStart();

    /// @brief Retorna se a animacao ja terminou ou não
    /// @return verdadeiro se a animacao terminou/falso caso contrario  
    bool isAnimationFinished(); 

  private:
    bool magic_animation_is_finished_;

    //Animações
    sf::Texture magic_texture_;
    sf::Sprite magic_sprite_;
    int number_of_frames_;
    int current_frame_;
    float animation_timer_;

};

#endif //MAGIC__H