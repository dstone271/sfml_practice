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


CollisionData CheckOOBBCollision(ControllableObject& object, CollidableObject& collidable) {
  // Set up collision data and helper variables
  CollisionData collision_result;
  collision_result.collision_occurred_ = true;
  collision_result.penetration_depth_ = std::numeric_limits<float>::max();

  // Do controllable object axis's first
  // Do x asix first
  sf::Vector2f a_corner0_a = object.size_;
  sf::Vector2f a_corner2_a = -object.size_;
  float a_min = a_corner2_a.x;
  float a_max = a_corner0_a.x;
  sf::Vector2f collison_normal(1.f, 0);

  sf::Vector2f[4] b_corners_a;
  b_corners_a[0] = collidable.size_;
  b_corners_a[0] = utility::TransformPointFromBasis(b_corners_a[0], collidable.position_, collidable.orientation_);
  b_corners_a[0] = utility::TransformPointToBasis(b_corners_a[0], object.position_, object.orientation_);
  b_conrers_a[1] = sf::Vector2f(- collidable.size_.x, collidable.size_.y);
  b_corners_a[1] = utility::TransformPointFromBasis(b_corners_a[1], collidable.position_, collidable.orientation_);
  b_corners_a[1] = utility::TransformPointToBasis(b_corners_a[1], object.position_, object.orientation_);
  b_conrers_a[2] = - collidable.size_;
  b_corners_a[2] = utility::TransformPointFromBasis(b_corners_a[2], collidable.position_, collidable.orientation_);
  b_corners_a[2] = utility::TransformPointToBasis(b_corners_a[2], object.position_, object.orientation_);
  b_conrers_a[3] = sf::Vector2f(collidable.size_.x, - collidable.size_.y);
  b_corners_a[3] = utility::TransformPointFromBasis(b_corners_a[3], collidable.position_, collidable.orientation_);
  b_corners_a[3] = utility::TransformPointToBasis(b_corners_a[3], object.position_, object.orientation_);

  float b_min = b_corners_a[0].x;
  float b_max = b_corners_a[0].x;
  sf::Vector2f b_corner_min = b_corners_a[0];
  sf::Vector2f b_corner_max = b_corners_a[0];
  for (int i = 1; i <= 3; i++) {
    if (b_corners_a[i].x < b_min) {
      b_min = b_corners_a[i].x;
      b_corner_min = b_corners_a[i];
    }
    else if (b_corners_a[i].x > b_max) {
      b_max = b_corners_a[i].x;
      b_corner_max = b_corners_a[i];
    }
  }

  // Calculate penetration depths
  bool collision_occurred;
  float penetration_depth;
  int collision_direction;
  collision_occurred = CalculateCollisionOnAxis(a_min, a_max, b_min, b_max, penetration_depth, collision_direction);

  // If no collision, then return
  if (collision_occurred == false) {
    collision_result.collision_occurred_ = false;
    return collision_result;
  }

  // Otherwise, there is a collision. Set collision data
  if (penetration_depth < collision_result.penetration_depth_) {
    collision_result.penetration_depth_ = penetration_depth;
    collision_normal = collision_normal * collision_direction;
    collision_normal = utility::TransformPointFromBasis(collision_normal, sf::Vector2f(0, 0), object.orientation_);
    collision_result.collision_normal_ = collision_normal;
    // This is becuase we are using A's x-axis
    if (collision_direction == -1) {
      collision_result.collision_point_local_ = sf::Vector2f(object.size_.x, b_corner_min.y);
    } else if (collision_direction == 1) {
      collision_result.collision_point_local_ = sf::Vector2f(- object.size_.x, b_corner_max.y);
    }
  }

  // Return collision data
  return collision_data;
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


