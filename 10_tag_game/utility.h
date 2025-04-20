#ifndef UTILITY_H
#define UTILITY_H

#include <SFML/System.hpp>
#include <cmath>


namespace utility {

// Returns unit vector of size 1 or the zero vector
sf::Vector2f GetUnitDirection(const sf::Vector2f& direction); 

} // namespace utility

#endif // UTILITY_H
