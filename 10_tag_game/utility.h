#ifndef UTILITY_H
#define UTILITY_H

#include <SFML/System.hpp>
#include <cmath>


namespace utility {

// Returns unit vector of size 1 or the zero vector
sf::Vector2f GetUnitDirection(const sf::Vector2f& direction); 

float DotProduct(const sf::Vector2f& vec_a, const sf::Vector2f& vec_b);

float Magnitude(const sf::Vector2f& vec);

float CalculateAngleDegrees(const sf::Vector2f& orientation);

sf::Vector2f GetOrientationFromDegrees(float degrees);

sf::Vector2f TransformPointFromBasis(const sf::Vector2f& point, const sf::Vector2f& position, const sf::Vector2f& orientation); 

sf::Vector2f TransformPointToBasis(const sf::Vector2f& point, const sf::Vector2f& position, const sf::Vector2f& orientation); 

} // namespace utility

#endif // UTILITY_H
