#ifndef CONTROL_INPUT_H
#define CONTROL_INPUT_H

#include <SFML/System.hpp>


struct ControlInput {
  // The normalized movement vector holds the direction of movement and the magnitude of movement on a scale from 0 to 1
  sf::Vector2f normalized_movement_ {};
};

#endif // CONTROL_INPUT_H
