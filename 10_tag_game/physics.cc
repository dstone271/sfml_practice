#include "physics.h"


void UpdateControllableObject(ControllableObject& object, const ControlInput& input, sf::Time elapsed_time) {
  object.velocity_ = input.normalized_movement_ * object.max_speed_;
  object.position_ += object.velocity_ * elapsed_time.asSeconds();
  object.object_.setPosition(object.position_);
}
