#include "utility.h"


namespace utility {

// Returns unit vector of size 1 or the zero vector
sf::Vector2f GetUnitDirection(const sf::Vector2f& direction) {
  sf::Vector2f unit_direction(0.f, 0.f);

  float magnitude = direction.x * direction.x;
  magnitude += direction.y * direction.y;
  magnitude = sqrt(magnitude);

  if (magnitude == 0) {
    return unit_direction;
  } else {
    unit_direction = direction / magnitude;
    return unit_direction;
  }
}

} // namespace utility
