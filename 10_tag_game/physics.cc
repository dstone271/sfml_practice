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
    //CollisionData collision = CheckCollision(object, collidable_list.GetObject(i));
    CollisionData collision = CheckOOBBCollision(object, collidable_list.GetObject(i));

    if (collision.collision_occurred_) {
      ResolveCollision(object, collision);
    }
  }
}


void CheckAndResolveCollisions(ParticleGun& particle_gun, ShatterBox& shatter_box) {
  sf::Vector2f box_pos = shatter_box.GetPosition();
  sf::Vector2f box_size = shatter_box.GetSize();
  float min_x = box_pos.x - (box_size.x / 2.0);
  float max_x = box_pos.x + (box_size.x / 2.0);
  float min_y = box_pos.y - (box_size.y / 2.0);
  float max_y = box_pos.y + (box_size.y / 2.0);
  int num_particles = particle_gun.GetNumParticles(); 
  bool collision = false;
  for (int i = 0; i < num_particles; i++) {
    sf::Vector2f particle_pos = particle_gun.GetParticlePos(i);
    if (particle_pos.x > min_x && particle_pos.x < max_x) {
      if (particle_pos.y > min_y && particle_pos.y < max_y) {
        collision = true;
        break;
      }
    }
  } 

  if (collision) {
    shatter_box.CollisionOccurred();
  }

  return;
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

  // Calculate min/max for each axis
  enum ObjectFrame { object_a, object_b, ObjectFrameLAST };
  enum ObjectAxis { axis_x, axis_y, ObjectAxisLAST };
  auto GetAxisValue = [](sf::Vector2f& vec, ObjectAxis axis) { 
    if (axis == axis_x) {
      //std::cout << "GetAxisValue - x" << std::endl;
      return vec.x;
    } else if (axis == axis_y) {
      //std::cout << "GetAxisValue - y" << std::endl;
      return vec.y;
    }
    std::cout << "GetAxisValue - neither :(" << std::endl;
    return 0.f;
  };
  for (int object_frame_int = object_a; object_frame_int != ObjectFrameLAST; object_frame_int++) {
    // ObjectFrame object
    ObjectFrame object_frame = static_cast<ObjectFrame>(object_frame_int);

    sf::Vector2f base_obj_size;
    sf::Vector2f base_obj_pos;
    sf::Vector2f base_obj_orient;
    sf::Vector2f transform_obj_size;
    sf::Vector2f transform_obj_pos;
    sf::Vector2f transform_obj_orient;

    if (object_frame == object_a) {
      base_obj_size = object.size_;
      base_obj_pos = object.position_;
      base_obj_orient = object.orientation_;
      transform_obj_size = collidable.size_;
      transform_obj_pos = collidable.position_;
      transform_obj_orient = collidable.orientation_;
    } else if (object_frame == object_b) {
      base_obj_size = collidable.size_;
      base_obj_pos = collidable.position_;
      base_obj_orient= collidable.orientation_;
      transform_obj_size = object.size_;
      transform_obj_pos = object.position_;
      transform_obj_orient = object.orientation_;
    }

    // Calculate corners of transformed object in base frame
    sf::Vector2f transform_obj_corners[4];
    transform_obj_corners[0] = transform_obj_size / 2.f;
    transform_obj_corners[0] = utility::TransformPointFromBasis(transform_obj_corners[0], transform_obj_pos, transform_obj_orient);
    transform_obj_corners[0] = utility::TransformPointToBasis(transform_obj_corners[0], base_obj_pos, base_obj_orient);
    transform_obj_corners[1] = sf::Vector2f(- transform_obj_size.x / 2.f, transform_obj_size.y / 2.f);
    transform_obj_corners[1] = utility::TransformPointFromBasis(transform_obj_corners[1], transform_obj_pos, transform_obj_orient);
    transform_obj_corners[1] = utility::TransformPointToBasis(transform_obj_corners[1], base_obj_pos, base_obj_orient);
    transform_obj_corners[2] = - transform_obj_size / 2.f;
    transform_obj_corners[2] = utility::TransformPointFromBasis(transform_obj_corners[2], transform_obj_pos, transform_obj_orient);
    transform_obj_corners[2] = utility::TransformPointToBasis(transform_obj_corners[2], base_obj_pos, base_obj_orient);
    transform_obj_corners[3] = sf::Vector2f(transform_obj_size.x / 2.f, - transform_obj_size.y / 2.f);
    transform_obj_corners[3] = utility::TransformPointFromBasis(transform_obj_corners[3], transform_obj_pos, transform_obj_orient);
    transform_obj_corners[3] = utility::TransformPointToBasis(transform_obj_corners[3], base_obj_pos, base_obj_orient);

    for (int object_axis_int = axis_x; object_axis_int != ObjectAxisLAST; object_axis_int++) {
      // ObjectAxis object
      ObjectAxis object_axis = static_cast<ObjectAxis>(object_axis_int);

      // min max values
      float base_max = GetAxisValue(base_obj_size, object_axis) / 2.f;
      float base_min = - base_max;
      float transform_min = GetAxisValue(transform_obj_corners[0], object_axis);
      float transform_max = transform_min;
      sf::Vector2f transform_corner_min = transform_obj_corners[0];
      sf::Vector2f transform_corner_max = transform_corner_min;
  
      for (int i = 1; i < 4; i++) {
        if (GetAxisValue(transform_obj_corners[i], object_axis) < transform_min) {
          transform_corner_min = transform_obj_corners[i];
          transform_min = GetAxisValue(transform_corner_min, object_axis);
        } else if (GetAxisValue(transform_obj_corners[i], object_axis) > transform_max) {
          transform_corner_max = transform_obj_corners[i];
          transform_max = GetAxisValue(transform_corner_max, object_axis);
        }
      }

      // Calculate penetration depths
      float a_min, a_max, b_min, b_max;
      if (object_frame == object_a) {
        a_min = base_min;
        a_max = base_max;
        b_min = transform_min;
        b_max = transform_max;
      } else if (object_frame == object_b) {
        a_min = transform_min;
        a_max = transform_max;
        b_min = base_min;
        b_max = base_max;
      }
      bool collision_occurred;
      float penetration_depth;
      int collision_direction;
      collision_occurred = CalculateCollisionOnAxis(a_min, a_max, b_min, b_max, penetration_depth, collision_direction);

      // Return if no collision
      if (collision_occurred == false) {
        collision_result.collision_occurred_ = false;
        return collision_result;
      }

      // Update collision data
      if (penetration_depth < collision_result.penetration_depth_) {
        collision_result.penetration_depth_ = penetration_depth;

        sf::Vector2f collision_norml_local;
        if (object_axis == axis_x) {
          collision_norml_local = sf::Vector2f(1.f * collision_direction, 0.f);
        } else if (object_axis == axis_y) {
          collision_norml_local = sf::Vector2f(0.f, 1.f * collision_direction);
        }

        collision_result.collision_normal_ = utility::TransformPointFromBasis(collision_norml_local, 
            sf::Vector2f(0, 0), base_obj_orient);

        sf::Vector2f collision_point;
        sf::Vector2f colliding_transform_point;
        if (collision_direction == 1) {
          colliding_transform_point = transform_corner_min;
        } else if (collision_direction == -1) {
          colliding_transform_point = transform_corner_max;
        }
        if (object_frame == object_b) {
          collision_point = utility::TransformPointFromBasis(colliding_transform_point, base_obj_pos, base_obj_orient);
          collision_point = utility::TransformPointToBasis(collision_point, transform_obj_pos, transform_obj_orient);
        } else if (object_axis == axis_x) {
          collision_point = sf::Vector2f(base_obj_size.x / (2.f * collision_direction), colliding_transform_point.y);
        } else if (object_axis == axis_y) {
          collision_point = sf::Vector2f(colliding_transform_point.x, base_obj_size.y / (2.f * collision_direction));
        }
        collision_result.collision_point_local_ = collision_point;

        /*collision_normal = collision_normal * (collision_direction * 1.f);
        collision_normal = utility::TransformPointFromBasis(collision_normal, sf::Vector2f(0, 0), object.orientation_);
        collision_result.collision_normal_ = collision_normal;
        // This is becuase we are using A's x-axis
        if (collision_direction == -1) {
          collision_result.collision_point_local_ = sf::Vector2f(object.size_.x / 2.f, b_corner_min.y);
        } else if (collision_direction == 1) {
          collision_result.collision_point_local_ = sf::Vector2f(- object.size_.x / 2.f, b_corner_max.y);
        }*/
      }

    } 
  }

  /* Old code for object a x axis
  // Do controllable object axis's first
  // Do x axis first
  sf::Vector2f a_corner0_a = object.size_ / 2.f;
  sf::Vector2f a_corner2_a = -object.size_ / 2.f;
  float a_min = a_corner2_a.x;
  float a_max = a_corner0_a.x;
  sf::Vector2f collision_normal(1.f, 0); // TODO - come back to

  sf::Vector2f b_corners_a[4];
  b_corners_a[0] = collidable.size_ / 2.f;
  b_corners_a[0] = utility::TransformPointFromBasis(b_corners_a[0], collidable.position_, collidable.orientation_);
  b_corners_a[0] = utility::TransformPointToBasis(b_corners_a[0], object.position_, object.orientation_);
  b_corners_a[1] = sf::Vector2f(- collidable.size_.x / 2.f, collidable.size_.y / 2.f);
  b_corners_a[1] = utility::TransformPointFromBasis(b_corners_a[1], collidable.position_, collidable.orientation_);
  b_corners_a[1] = utility::TransformPointToBasis(b_corners_a[1], object.position_, object.orientation_);
  b_corners_a[2] = - collidable.size_ / 2.f;
  b_corners_a[2] = utility::TransformPointFromBasis(b_corners_a[2], collidable.position_, collidable.orientation_);
  b_corners_a[2] = utility::TransformPointToBasis(b_corners_a[2], object.position_, object.orientation_);
  b_corners_a[3] = sf::Vector2f(collidable.size_.x / 2.f, - collidable.size_.y / 2.f);
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
    collision_normal = collision_normal * (collision_direction * 1.f);
    collision_normal = utility::TransformPointFromBasis(collision_normal, sf::Vector2f(0, 0), object.orientation_);
    collision_result.collision_normal_ = collision_normal;
    // This is becuase we are using A's x-axis
    if (collision_direction == -1) {
      collision_result.collision_point_local_ = sf::Vector2f(object.size_.x / 2.f, b_corner_min.y);
    } else if (collision_direction == 1) {
      collision_result.collision_point_local_ = sf::Vector2f(- object.size_.x / 2.f, b_corner_max.y);
    }
  }*/


  // Return collision data
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


bool CalculateCollisionOnAxis(float a_min, float a_max, float b_min, float b_max, float& penetration_depth,
    int& collision_direction) {
  // left of object b
  float left_penetration = a_max - b_min;
  // right of object b
  float right_penetration = b_max - a_min;

  if (left_penetration >= 0 && right_penetration >= 0) {
    if (left_penetration < right_penetration) {
      penetration_depth = left_penetration;
      collision_direction = -1;
    } else {
      penetration_depth = right_penetration;
      collision_direction = 1;
    } 
    return true;
  }

  return false;
}


