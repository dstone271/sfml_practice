#ifndef SHATTER_BOX_H
#define SHATTER_BOX_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "shatter_emitter.h"


class ShatterBox {
 public:
  sf::RectangleShape object_ {};

  void Update(sf::Time elapsed_time);
  void SetPosition(float x_val, float y_val);
  void SetSize(float x_val, float y_val);
  void Draw(sf::RenderWindow &window);
  sf::Vector2f GetPosition();
  sf::Vector2f GetSize();
  void CollisionOccurred();

 private:
  sf::Vector2f position_ {};
  sf::Vector2f size_ {};
  bool display_ {true};
  float respawn_life_ {};
  ShatterEmitter shatter_emitter_ {};
};

#endif // SHATTER_BOX_H
