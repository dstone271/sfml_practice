#include "utility.h"

namespace {
  const float PI = 3.1415926536;
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


sf::Vector2f TransformPointFromBasis(const sf::Vector2f& point, const sf::Vector2f& position, const sf::Vector2f& orientation) {
  sf::Vector2f transformed_point;

  // rotate
  float rotation_degrees = CalculateAngleDegrees(orientation);
  float magnitude = Magnitude(point);
  float current_angle_radians = std::atan(point.y / point.x);
  if (point.x < 0) {
    current_angle_radians += PI;
  }
  float new_angle_radians = current_angle_radians + (rotation_degrees * PI / 180.0);
  transformed_point.x = magnitude * std::cos(new_angle_radians);
  transformed_point.y = magnitude * std::sin(new_angle_radians);

  // translate
  transformed_point += position;

  return transformed_point;
}


sf::Vector2f TransformPointToBasis(const sf::Vector2f& point, const sf::Vector2f& position, const sf::Vector2f& orientation) {
  sf::Vector2f transformed_point = point;

  // translate with negative position
  transformed_point -= position;

  // rotate with negative orientation
  float rotation_degrees = -1.0 * CalculateAngleDegrees(orientation);
  float magnitude = Magnitude(transformed_point);
  float current_angle_radians = std::atan(transformed_point.y / transformed_point.x);
  if (transformed_point.x < 0) {
    current_angle_radians += PI;
  }
  float new_angle_radians = current_angle_radians + (rotation_degrees * PI / 180.0);
  transformed_point.x = magnitude * std::cos(new_angle_radians);
  transformed_point.y = magnitude * std::sin(new_angle_radians);

  return transformed_point;
}


} // namespace utility
