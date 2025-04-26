#ifndef CONTROLLABLE_OBJECT_H
#define CONTROLLABLE_OBJECT_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

// local configuration variables
namespace {
  const float MAX_SPEED = 300;
}


enum class ControlType {
  instant_accel,
  constant_accel,
  proportional_accel,
};


struct ControllableObject {
  sf::Sprite object_ {};
  sf::Vector2f position_ {};
  sf::Vector2f size_ {};

  // Velocity and speed are in pixels per second
  sf::Vector2f velocity_ {};
  float max_speed_ = MAX_SPEED;
  ControlType control_type_ = ControlType::instant_accel;
};


#endif // CONTROLLABLE_OBJECT_H
