#include "physics.h"

namespace {
  const float MOVEMENT_ACCEL = 1500;
  const float BASE_ACCEL = 200;
  const float ACCEL_SLOPE = 10;
  const float ANGULAR_VELOCITY = 90;
}


void UpdateControllableObject(ControllableObject& object, const ControlInput& input, sf::Time elapsed_time) {
  sf::Vector2f velocity_error = (input.normalized_movement_ * object.max_speed_) - object.velocity_;
  
  switch (object.control_type_) {
    case ControlType::instant_accel:
      object.velocity_ = input.normalized_movement_ * object.max_speed_;
      object.position_ += object.velocity_ * elapsed_time.asSeconds();
      break;
    case ControlType::constant_accel:
      object.velocity_ += utility::GetUnitDirection(velocity_error) * MOVEMENT_ACCEL * elapsed_time.asSeconds();
      object.position_ += object.velocity_ * elapsed_time.asSeconds();
      break;
    case ControlType::proportional_accel:
      float accel = (utility::Magnitude(velocity_error) * ACCEL_SLOPE) + BASE_ACCEL;
      object.velocity_ += utility::GetUnitDirection(velocity_error) * accel * elapsed_time.asSeconds();
      object.position_ += object.velocity_ * elapsed_time.asSeconds();
      break;
  }

  // Update object orientation
  float rotation_degrees = utility::CalculateAngleDegrees(object.orientation_);
  if (input.rotation_direction_ == RotationDirection::clockwise) {
    rotation_degrees += ANGULAR_VELOCITY * elapsed_time.asSeconds();
  } else if (input.rotation_direction_ == RotationDirection::counter_clockwise) {
    rotation_degrees -= ANGULAR_VELOCITY * elapsed_time.asSeconds();
  }
  object.orientation_ = utility::GetOrientationFromDegrees(rotation_degrees);

  // Set position and orientation for graphics object
  object.object_.setPosition(object.position_);
  object.object_.setRotation(utility::CalculateAngleDegrees(object.orientation_));
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
  CollisionData collision_result;
  sf::Vector2i collision_axis;

  // check x-axis
  float x_penetration_left = (object.position_.x + (object.size_.x / 2.f)) - (collidable.position_.x - (collidable.size_.x / 2.f));
  float x_penetration_right = (collidable.position_.x + (collidable.size_.x / 2.f)) - (object.position_.x - (object.size_.x / 2.f));
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
  float y_penetration_up = (object.position_.y + (object.size_.y / 2.f)) - (collidable.position_.y - (collidable.size_.y / 2.f));
  float y_penetration_down = (collidable.position_.y + (collidable.size_.y / 2.f)) - (object.position_.y - (object.size_.y / 2.f));
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


