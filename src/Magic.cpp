#include "Magic.h"


Magic::Magic(std::string magic_type) {
  magic_sprite_ = sf::Sprite();
  current_frame_ = 0;
  animation_timer_ = 0.0f;
  magic_animation_is_finished_ = true;

  if(magic_type == "fireball") {
    number_of_frames_ = 14;
    magic_texture_.loadFromFile("Textures/Creation-Sheet.png");
    magic_sprite_.setTexture(magic_texture_);
    magic_sprite_.setTextureRect(sf::IntRect(0, 0, 64, 64));
  }
  else if(magic_type == "buffskill") {
    number_of_frames_ = 4;
    magic_texture_.loadFromFile("Textures/HalflingAssassinIdleSideBuff.png");
    magic_sprite_.setTexture(magic_texture_);
    magic_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
  }
  else if(magic_type == "healskill") {
    number_of_frames_ = 4;
    magic_texture_.loadFromFile("Textures/RadiantPaladinIdleSideHeal.png");
    magic_sprite_.setTexture(magic_texture_);
    magic_sprite_.setTextureRect(sf::IntRect(0, 0, 16, 16));
  }
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

void Magic::buffMagicAnimation(float delta_time) {
  float animation_interval = 0.5f;
  animation_timer_ += delta_time;

  if(animation_timer_ > animation_interval) {
    current_frame_ = (current_frame_ + 1)%number_of_frames_;

    int frame_width = magic_texture_.getSize().x / number_of_frames_;
    int frame_height = magic_texture_.getSize().y;
    magic_sprite_.setTextureRect(sf::IntRect(current_frame_ * frame_width, 0, frame_width, frame_height));

    animation_timer_ = 0.0f;
  }
  if((current_frame_+1)%4 == 0) magic_animation_is_finished_ = true;
}

void Magic::healMagicAnimation(float delta_time) {
  float animation_interval = 0.5f;
  animation_timer_ += delta_time;

  if(animation_timer_ > animation_interval) {
    current_frame_ = (current_frame_ + 1)%number_of_frames_;

    int frame_width = magic_texture_.getSize().x / number_of_frames_;
    int frame_height = magic_texture_.getSize().y;
    magic_sprite_.setTextureRect(sf::IntRect(current_frame_ * frame_width, 0, frame_width, frame_height));

    animation_timer_ = 0.0f;
  }
  if((current_frame_+1)%4 == 0) magic_animation_is_finished_ = true;
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

