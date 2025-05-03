#ifndef COLLIDABLE_OBJECT_LIST_H
#define COLLIDABLE_OBJECT_LIST_H

#include <vector>
#include <SFML/System.hpp>

#include "collidable_object.h"
#include "utility.h"


class CollidableObjectList {
 private:
  std::vector<CollidableObject> object_list_;

 public:
  void CreateNewObject(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& orienation);
  void AddObject(const CollidableObject& new_object);
  CollidableObject& GetObject(int index);
  int GetSize();
};

#endif // COLLIDABLE_OBJECT_LIST_H
