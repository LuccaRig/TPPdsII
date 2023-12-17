#include "Magic.h"


Magic::Magic() {
  magic_sprite_ = sf::Sprite();
  number_of_frames_ = 14;
  current_frame_ = 0;
  animation_timer_ = 0.0f;
  magic_animation_is_finished_ = true;

  magic_texture_.loadFromFile("Textures/Creation-Sheet.png");
  magic_sprite_.setTexture(magic_texture_);
  magic_sprite_.setTextureRect(sf::IntRect(0, 0, 64, 64));
}

void Magic::attackMagicAnimation(float delta_time) {
  float animation_interval = 1.5f;
  animation_timer_ += delta_time;

  if(animation_timer_ > animation_interval) {
    current_frame_ = (current_frame_ + 1)%number_of_frames_;

    int frame_width = magic_texture_.getSize().x / number_of_frames_;
    int frame_height = magic_texture_.getSize().y;
    magic_sprite_.setTextureRect(sf::IntRect(current_frame_ * frame_width, 0, frame_width, frame_height));

    animation_timer_ = 0.0f;
  }
  if((current_frame_+1)%14 == 0) magic_animation_is_finished_ = true;
}

sf::Sprite& Magic::get_magic_sprite() {
  return magic_sprite_;
}

void Magic::finishMagicAnimation() {
  magic_animation_is_finished_ = true;
}

void Magic::magicAnimationStart() {
  magic_animation_is_finished_ = false;
}

void Magic::set_frame_zero() {
  current_frame_ = 0;
}

bool Magic::isAnimationFinished() {
  return magic_animation_is_finished_;
}

