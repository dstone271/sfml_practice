#include "utility.h"


namespace utility {


// Returns unit vector of size 1 or the zero vector
sf::Vector2f GetUnitDirection(const sf::Vector2f& direction) {
  sf::Vector2f unit_direction(0.f, 0.f);

  float magnitude = Magnitude(direction);

  if (magnitude == 0) {
    return unit_direction;
  } else {
    unit_direction = direction / magnitude;
    return unit_direction;
  }
}


float DotProduct(const sf::Vector2f& vec_a, const sf::Vector2f& vec_b) {
  return (vec_a.x * vec_b.x) + (vec_a.y * vec_b.y);
}


float Magnitude(const sf::Vector2f& vec) {
  float magnitude = vec.x * vec.x;
  magnitude += vec.y * vec.y;
  magnitude = sqrt(magnitude);
  return magnitude;
}


} // namespace utility
