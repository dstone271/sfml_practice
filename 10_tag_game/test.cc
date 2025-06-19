#include <SFML/System.hpp>
#include <iostream>

#include "utility.h"
#include "physics.h"
#include "controllable_object.h"
#include "collidable_object.h"


int main() {
  // Test transform functions
  sf::Vector2f point_orig(1.f, 1.f);
  sf::Vector2f basis_pos(2.f, 1.f);
  sf::Vector2f basis_orient(0.f, 1.f);
  sf::Vector2f point_new = utility::TransformPointFromBasis(point_orig, basis_pos, basis_orient);
  std::cout << "Test Transform From Basis: " << (point_new.x == 1 && point_new.y == 2) << std::endl;

  sf::Vector2f point_orig_calc = utility::TransformPointToBasis(point_new, basis_pos, basis_orient);
  std::cout << "Original point y: " << point_orig.y << ", new point y: " << point_new.y << 
    ", calc point y: " << point_orig_calc.y << std::endl;
  std::cout << "Test Transform To Basis: " << (point_orig_calc.y == 1) << std::endl; // && point_orig_calc.x == 1.f


  // Test Physics CalculateCollisionOnAxis
  float b_min = -1.f;
  float b_max = 1.f;
  float a_min = -3.f;
  float a_max = -2.f;
  float penetration_depth;
  int collision_direction;
  bool collision_occurred;

  collision_occurred = CalculateCollisionOnAxis(a_min, a_max, b_min, b_max, penetration_depth, collision_direction);
  std::cout << "Test collision: " << (collision_occurred == false) << std::endl; 
  
  a_min = -1.5;
  a_max = 0.f;
  collision_occurred = CalculateCollisionOnAxis(a_min, a_max, b_min, b_max, penetration_depth, collision_direction);
  std::cout << "Test collision: " << (collision_occurred == true) << std::endl; 
  std::cout << "Test penetration depth: " << (penetration_depth == 1.f) << 
    " (Expected: 1.0, Actual: " << penetration_depth << ")" << std::endl;
  std::cout << "Test collision direction: " << (collision_direction == -1) << std::endl;

  a_min = 0.5f;
  a_max = 1.5f;
  collision_occurred = CalculateCollisionOnAxis(a_min, a_max, b_min, b_max, penetration_depth, collision_direction);
  std::cout << "Test collision: " << (collision_occurred == true) << std::endl; 
  std::cout << "Test penetration depth: " << (penetration_depth == 0.5f) << 
    " (Expected: 0.5, Actual: " << penetration_depth << ")" << std::endl;
  std::cout << "Test collision direction: " << (collision_direction == 1) << std::endl;

  a_min = 1.5f;
  a_max = 2.5f;
  collision_occurred = CalculateCollisionOnAxis(a_min, a_max, b_min, b_max, penetration_depth, collision_direction);
  std::cout << "Test collision: " << (collision_occurred == false) << std::endl; 


  // Test Physics CheckOOBBCollision
  ControllableObject obj_a; // left side diagnol
  obj_a.position_ = sf::Vector2f(-150, 0);
  obj_a.orientation_ = sf::Vector2f(0.7071f, 0.7071f);
  obj_a.size_ = sf::Vector2f(100, 100);
  CollidableObject obj_b;
  obj_b.position_ = sf::Vector2f(0, 0);
  obj_b.orientation_ = sf::Vector2f(1, 0);
  obj_b.size_ = sf::Vector2f(100, 100);
  CollisionData collision_result = CheckOOBBCollision(obj_a, obj_b);
  std::cout << "1. Test no collision: " << (collision_result.collision_occurred_ == false) << std::endl;

  obj_a.position_ = sf::Vector2f(0, 150); // under normal
  obj_a.orientation_ = sf::Vector2f(1, 0);
  collision_result = CheckOOBBCollision(obj_a, obj_b);
  std::cout << "2. Test no collision: " << (collision_result.collision_occurred_ == false) << std::endl;

  obj_a.position_ = sf::Vector2f(0, -100); // above diagnol collision
  obj_a.orientation_ = sf::Vector2f(0.7071f, 0.7071f);
  collision_result = CheckOOBBCollision(obj_a, obj_b);
  std::cout << "3: Test collision: " << (collision_result.collision_occurred_ == true) << std::endl;
  std::cout << "3: Test normal: " << 
    (collision_result.collision_normal_.x == 0 && collision_result.collision_normal_.y == -1) << std::endl;
  std::cout << "3: Test penetration depth: " << (collision_result.penetration_depth_ == 20.710678) << std::endl;
  std::cout << "3: Test collision point: " << 
    (collision_result.collision_point_local_.x == 50 && collision_result.collision_point_local_.y == 50) << std::endl;

  obj_a.position_ = sf::Vector2f(-60, 60); // bottom left diagnol collide
  obj_a.orientation_ = sf::Vector2f(0.7071f, 0.7071f);
  collision_result = CheckOOBBCollision(obj_a, obj_b);
  std::cout << "4: Test collision: " << (collision_result.collision_occurred_ == true) << std::endl;
  std::cout << "4: Test normal: " << 
    (collision_result.collision_normal_.x == -0.7071f && collision_result.collision_normal_.y == 0.7071f) << std::endl;
  std::cout << "4: Test penetration depth: " << (collision_result.penetration_depth_ == 35.857864) << std::endl;
  std::cout << "4: Test collision point: " << 
    (collision_result.collision_point_local_.x == 0 && collision_result.collision_point_local_.y == -50) << std::endl;

  obj_a.position_ = sf::Vector2f(-200, 0); // b diag, left diag
  obj_a.orientation_ = sf::Vector2f(0.7071f, 0.7071f);
  obj_b.orientation_ = sf::Vector2f(0.7071f, -0.7071f);
  collision_result = CheckOOBBCollision(obj_a, obj_b);
  std::cout << "5: Test no collision: " << (collision_result.collision_occurred_ == false) << std::endl;

  obj_a.position_ = sf::Vector2f(0, 150); // b diag, under normal
  obj_a.orientation_ = sf::Vector2f(1, 0);
  obj_b.orientation_ = sf::Vector2f(0.7071f, -0.7071f);
  collision_result = CheckOOBBCollision(obj_a, obj_b);
  std::cout << "6: Test no collision: " << (collision_result.collision_occurred_ == false) << std::endl;
  
  obj_a.position_ = sf::Vector2f(0, -100); // b diag, above normal collision
  obj_a.orientation_ = sf::Vector2f(1, 0);
  obj_b.orientation_ = sf::Vector2f(0.7071f, -0.7071f);
  collision_result = CheckOOBBCollision(obj_a, obj_b);
  std::cout << "7: Test collision: " << (collision_result.collision_occurred_ == true) << std::endl;
  std::cout << "7: Test normal: " << 
    (collision_result.collision_normal_.x == 0 && collision_result.collision_normal_.y == -1) << std::endl;
  std::cout << "7: Test penetration depth: " << (collision_result.penetration_depth_ == 20.710678) << std::endl;
  std::cout << "7: Test collision point: " << 
    (collision_result.collision_point_local_.x == 0 && collision_result.collision_point_local_.y == 50) << std::endl;
  
  obj_a.position_ = sf::Vector2f(-60, 60); // b diag, bottom left normal collide
  obj_a.orientation_ = sf::Vector2f(1, 0);
  obj_b.orientation_ = sf::Vector2f(0.7071f, -0.7071f);
  collision_result = CheckOOBBCollision(obj_a, obj_b);
  std::cout << "8: Test collision: " << (collision_result.collision_occurred_ == true) << std::endl;
  std::cout << "8: Test normal: " << 
    (collision_result.collision_normal_.x == -0.7071f && collision_result.collision_normal_.y == 0.7071f) << std::endl;
  std::cout << "8: Test penetration depth: " << (collision_result.penetration_depth_ == 35.857864) << std::endl;
  std::cout << "8: Test collision point: " << 
    (collision_result.collision_point_local_.x == 50 && collision_result.collision_point_local_.y == 50) << std::endl;

  //obj_a.position_ = sf::Vector2f(-65.f, -65.f);
  //obj_a.orientation_ = sf::Vector2f();

  return 0;
}

