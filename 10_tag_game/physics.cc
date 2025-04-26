#include "physics.h"

namespace {
  const float MOVEMENT_ACCEL = 200;
  const float BASE_ACCEL = 200;
  const float ACCEL_SLOPE = 10;
}


void UpdateControllableObject(ControllableObject& object, const ControlInput& input, sf::Time elapsed_time) {
  sf::Vector2f velocity_error = (input.normalized_movement_ * object.max_speed_) - object.velocity_;
  
  switch (object.control_type_) {
    case ControlType::instant_accel:
      object.velocity_ = input.normalized_movement_ * object.max_speed_;
      object.position_ += object.velocity_ * elapsed_time.asSeconds();
      object.object_.setPosition(object.position_);
      break;
    case ControlType::constant_accel:
      object.velocity_ += utility::GetUnitDirection(velocity_error) * MOVEMENT_ACCEL * elapsed_time.asSeconds();
      object.position_ += object.velocity_ * elapsed_time.asSeconds();
      object.object_.setPosition(object.position_);
      break;
    case ControlType::proportional_accel:
      float accel = (utility::Magnitude(velocity_error) * ACCEL_SLOPE) + BASE_ACCEL;
      object.velocity_ += utility::GetUnitDirection(velocity_error) * accel * elapsed_time.asSeconds();
      object.position_ += object.velocity_ * elapsed_time.asSeconds();
      object.object_.setPosition(object.position_);
      break;
  }
}


void CheckAndResolveCollisions(ControllableObject& object, CollidableObjectList& collidable_list) {
  for (int i = 0; i < collidable_list.GetSize(); i++) {
    CollisionData collision = CheckCollision(object, collidable_list.GetObject(i));

    if (collision.collision_occurred_) {
      ResolveCollision(object, collision);
    }
  }
}


CollisionData CheckCollision(ControllableObject& object, CollidableObject& collidable) {
  // collision occurred
  // collision normal
  // penetration depth
  CollisionData collision_result;
  sf::Vector2i collision_axis;

  // check x-axis
  float x_penetration_left = (object.position_.x + object.size_.x) - collidable.position_.x;
  float x_penetration_right = (collidable.position_.x + collidable.size_.x) - object.position_.x;
  float x_penetration;
  if (x_penetration_left < x_penetration_right) {
    x_penetration = x_penetration_left;
    collision_axis.x = -1;
  } else {
    x_penetration = x_penetration_right;
    collision_axis.x = 1;
  }

  if (x_penetration < 0) {
    collision_result.collision_occurred_ = false;
    return collision_result;
  }
  
  // check y-axis
  float y_penetration_up = (object.position_.y + object.size_.y) - collidable.position_.y;
  float y_penetration_down = (collidable.position_.y + collidable.size_.y) - object.position_.y;
  float y_penetration;
  if (y_penetration_up < y_penetration_down) {
    y_penetration = y_penetration_up;
    collision_axis.y = -1;
  } else {
    y_penetration = y_penetration_down;
    collision_axis.y = 1;
  }

  if (y_penetration < 0) {
    collision_result.collision_occurred_ = false;
    return collision_result;
  }

  // collision occurred - get collision data
  collision_result.collision_occurred_ = true;
  if (x_penetration < y_penetration) {
    collision_result.penetration_depth_ = x_penetration;
    collision_result.collision_normal_ = sf::Vector2f(collision_axis.x, 0);
  } else {
    collision_result.penetration_depth_ = y_penetration;
    collision_result.collision_normal_ = sf::Vector2f(0, collision_axis.y);
  }

  return collision_result;
}


void ResolveCollision(ControllableObject& object, CollisionData& collision) {
  if (collision.collision_occurred_ == false) {
    return;
  }

  object.position_ = object.position_ + (collision.collision_normal_ * collision.penetration_depth_);
  float velocity_change = utility::DotProduct(object.velocity_, collision.collision_normal_);
  if (velocity_change < 0) {
    object.velocity_ = object.velocity_ + (collision.collision_normal_ * velocity_change * -1.f);
  }
}


