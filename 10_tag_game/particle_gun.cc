#include "particle_gun.h"


void ParticleGun::Update(const ControlInput& input, sf::Time elapsed_time) {
  // Update emitter object
  velocity_ = input.normalized_movement_ * max_speed_;
  position_ += velocity_ * elapsed_time.asSeconds();
  float rotation_degrees = utility::CalculateAngleDegrees(orientation_);
  if (input.rotation_direction_ == RotationDirection::clockwise) {
    rotation_degrees += rotation_speed_ * elapsed_time.asSeconds();
  } else if (input.rotation_direction_ == RotationDirection::counter_clockwise) {
    rotation_degrees -= rotation_speed_ * elapsed_time.asSeconds();
  }
  orientation_ = utility::GetOrientationFromDegrees(rotation_degrees);
  object_.setPosition(position_);
  object_.setRotation(utility::CalculateAngleDegrees(orientation_));

  // Create paritcle from action
  if (input.action0) {
    Particle new_particle;
    new_particle.SetPosition(position_.x, position_.y);
    sf::Vector2f new_velocity = particle_speed_ * orientation_;
    new_particle.SetVelocity(new_velocity.x, new_velocity.y);
    new_particle.SetAcceleration(0, 0);
    new_particle.SetInverseMass(1);
    new_particle.SetDamping(0.999);
    new_particle.SetLife(3.0);
    new_particle.SetGenerations(0);
    particle_list_.push_back(new_particle);
  }

  // Update Particles
  for (int i = 0; i < particle_list_.size(); i++) {
    Particle &current_particle = particle_list_[i];
    current_particle.Integrate(elapsed_time);
    if (current_particle.GetLife() <= 0.0) {
      // Delete particle
      particle_list_.erase(particle_list_.begin() + i);
    }
  }

  return;
}


void ParticleGun::SetPosition(float x_val, float y_val) {
  position_.x = x_val;
  position_.y = y_val;
}


void ParticleGun::SetVelocity(float x_val, float y_val) {
  velocity_.x = x_val;
  velocity_.y = y_val;
}


void ParticleGun::SetOrientation(float x_val, float y_val) {
  orientation_.x = x_val;
  orientation_.y = y_val;
}


void ParticleGun::SetSize(float x_val, float y_val) {
  sf::Vector2f size_vector;
  size_vector.x = x_val;
  size_vector.y = y_val;
  object_.setSize(size_vector);
  object_.setOrigin(size_vector / 2.f);
}


void ParticleGun::Draw(sf::RenderWindow &window) {
  window.draw(object_);
  for (int i = 0; i < particle_list_.size(); i++) {
    window.draw(particle_list_[i].object_);
  }

  return;
}


int ParticleGun::GetNumParticles() {
  return particle_list_.size();
}


sf::Vector2f ParticleGun::GetParticlePos(int index) {
  return particle_list_[index].GetPosition();
}

