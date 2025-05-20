#ifndef CONTROL_INPUT_H
#define CONTROL_INPUT_H

#include <SFML/System.hpp>


enum class RotationDirection {
  no_rotation,
  clockwise,
  counter_clockwise,
};

struct ControlInput {
  // The normalized movement vector holds the direction of movement and the magnitude of movement on a scale from 0 to 1
  sf::Vector2f normalized_movement_ {};

  // Clockwise is +1, Counter-clockwise is -1, no rotation is 0
  RotationDirection rotation_direction_ {};
};

#endif // CONTROL_INPUT_H
