#include "collidable_object_list.h"


void CollidableObjectList::CreateNewObject(const sf::Vector2f& position, const sf::Vector2f& size) {
  CollidableObject new_object;
  new_object.position_ = position;
  new_object.size_ = size;
  new_object.object_.setSize(size);
  new_object.object_.setPosition(position);
  new_object.object_.setFillColor(sf::Color::Red);

  object_list_.push_back(new_object);
}


void CollidableObjectList::AddObject(const CollidableObject& new_object) {
  object_list_.push_back(new_object);
}


CollidableObject& CollidableObjectList::GetObject(int index) {
  return object_list_[index];
}


int CollidableObjectList::GetSize() {
  return object_list_.size();
}
