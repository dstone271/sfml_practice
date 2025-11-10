#include "shatter_box.h"


void ShatterBox::Update(sf::Time elapsed_time) {
  if (display_ == false) {
    respawn_life_ -= elapsed_time.asSeconds();
  }
  if (respawn_life_ <= 0.0) {
    display_ = true;
  }

  if (shatter_emitter_.IsActive()) {
    shatter_emitter_.Update(elapsed_time);
  }

  return;
}


void ShatterBox::SetPosition(float x_val, float y_val) {
  position_.x = x_val;
  position_.y = y_val;
  object_.setPosition(position_);
}


void ShatterBox::SetSize(float x_val, float y_val) {
  size_.x = x_val;
  size_.y = y_val;
  object_.setSize(size_);
  object_.setOrigin(size_ / 2.f);
}


void ShatterBox::Draw(sf::RenderWindow &window) {
  if (display_) {
    window.draw(object_);
  }

  if (shatter_emitter_.IsActive()) {
    shatter_emitter_.Draw(window);
  }
}


sf::Vector2f ShatterBox::GetPosition() {
  return position_;
}


sf::Vector2f ShatterBox::GetSize() {
  return size_;
}


void ShatterBox::CollisionOccurred() {
  display_ = false;
  respawn_life_ = 2.0;
  shatter_emitter_.Activate(position_, size_);
}
