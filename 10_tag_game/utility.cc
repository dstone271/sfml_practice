#include "utility.h"

namespace {
  const float PI = 3.14159;
}

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


float CalculateAngleDegrees(const sf::Vector2f& orientation) {
  float theta = std::acos(orientation.x);
  if (orientation.y < 0) {
    theta += 2 * (PI - theta);
  }
  theta *= 360.f / (2.f * PI);
  return theta;
}


sf::Vector2f GetOrientationFromDegrees(float degrees) {
  sf::Vector2f orientation;
  float rotation_radians = degrees * PI / 180.0;
  orientation.x = std::cos(rotation_radians);
  orientation.y = std::sin(rotation_radians);
  return orientation;
}


} // namespace utility
