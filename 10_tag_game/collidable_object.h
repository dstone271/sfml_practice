#ifndef COLLIDABLE_OBJECT_H
#define COLLIDABLE_OBJECT_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


struct CollidableObject {
  sf::RectangleShape object_ {};
  sf::Vector2f position_ {};
  sf::Vector2f size_ {};
};

#endif // COLLIDABLE_OBJECT_H
