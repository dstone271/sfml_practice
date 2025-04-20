#ifndef CONTROLLABLE_OBJECT_H
#define CONTROLLABLE_OBJECT_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

// local configuration variables
namespace {
  const float MAX_SPEED = 100;
}


struct ControllableObject {
  sf::Sprite object_ {};
  sf::Vector2f position_ {};

  // Velocity and speed are in pixels per second
  sf::Vector2f velocity_ {};
  float max_speed_ = MAX_SPEED;
};

#endif // CONTROLLABLE_OBJECT_H
