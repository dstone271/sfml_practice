#ifndef PHYSICS_H
#define PHYSICS_H

#include <SFML/System.hpp>

#include "controllable_object.h"
#include "collidable_object_list.h"
#include "collidable_object.h"
#include "control_input.h"
#include "utility.h"


struct CollisionData {
  bool collision_occurred_ = false;
  sf::Vector2f collision_normal_;
  float penetration_depth_;
};

void UpdateControllableObject(ControllableObject& object, const ControlInput& input, sf::Time elapsed_time); 

void CheckAndResolveCollisions(ControllableObject& object, CollidableObjectList& collidable_list);

CollisionData CheckCollision(ControllableObject& object, CollidableObject& collidable); 

void ResolveCollision(ControllableObject& object, CollisionData& collision); 

#endif // PHYSICS_H
