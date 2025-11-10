#ifndef PHYSICS_H
#define PHYSICS_H

#include <SFML/System.hpp>
#include <limits>
#include <iostream>

#include "controllable_object.h"
#include "collidable_object_list.h"
#include "collidable_object.h"
#include "control_input.h"
#include "utility.h"
#include "particle_gun.h"
#include "shatter_box.h"
#include "particle.h"


struct CollisionData {
  bool collision_occurred_ = false;
  sf::Vector2f collision_normal_;
  float penetration_depth_;
  sf::Vector2f collision_point_local_;
};

void UpdateControllableObject(ControllableObject& object, const ControlInput& input, sf::Time elapsed_time); 

void CheckAndResolveCollisions(ControllableObject& object, CollidableObjectList& collidable_list);

void CheckAndResolveCollisions(ParticleGun& particle_gun, ShatterBox& shatter_box);

CollisionData CheckCollision(ControllableObject& object, CollidableObject& collidable); 

CollisionData CheckOOBBCollision(ControllableObject& object, CollidableObject& collidable); 

void ResolveCollision(ControllableObject& object, CollisionData& collision); 

bool CalculateCollisionOnAxis(float a_min, float a_max, float b_min, float b_max, float& penetration_depth,
    int& collision_direction);

#endif // PHYSICS_H
