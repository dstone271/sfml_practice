#include "particle_emitter.h"


void ParticleEmitter::Update(const ControlInput& input, sf::Time elapsed_time) {
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
    sf::Vector2f new_velocity = velocity_ + (particle_speed_ * orientation_);
    new_particle.SetVelocity(new_velocity.x, new_velocity.y);
    new_particle.SetAcceleration(0, 300);
    new_particle.SetInverseMass(1);
    new_particle.SetDamping(0.999);
    new_particle.SetLife(1.0);
    new_particle.SetGenerations(2);
    particle_list_.push_back(new_particle);
  }

  // Update Particles
  for (int i = 0; i < particle_list_.size(); i++) {
    Particle &current_particle = particle_list_[i];
    current_particle.Integrate(elapsed_time);
    if (current_particle.GetLife() <= 0.0) {
      int spawn_generations = current_particle.GetGenerations();
      if (spawn_generations > 0) {
        SpawnChildParticles(current_particle);
      }

      // Delete particle
      particle_list_.erase(particle_list_.begin() + i);
    }
  }

  return;
}


void ParticleEmitter::SetPosition(float x_val, float y_val) {
  position_.x = x_val;
  position_.y = y_val;
}


void ParticleEmitter::SetVelocity(float x_val, float y_val) {
  velocity_.x = x_val;
  velocity_.y = y_val;
}


void ParticleEmitter::SetOrientation(float x_val, float y_val) {
  orientation_.x = x_val;
  orientation_.y = y_val;
}


void ParticleEmitter::SetSize(float x_val, float y_val) {
  sf::Vector2f size_vector;
  size_vector.x = x_val;
  size_vector.y = y_val;
  object_.setSize(size_vector);
  object_.setOrigin(size_vector / 2.f);
}


void ParticleEmitter::SpawnChildParticles(Particle parent_particle) {
  sf::Vector2f pos = parent_particle.GetPosition();
  sf::Vector2f base_vel = parent_particle.GetVelocity();
  int spawn_generations = parent_particle.GetGenerations() - 1;
  for (int i = 0; i < nr_child_particles_; i++) {
    Particle new_particle;
    new_particle.SetPosition(pos.x, pos.y);
    float dir_rad = i * 6.283 / nr_child_particles_;
    sf::Vector2f burst_vel = burst_speed_ * sf::Vector2f(std::cos(dir_rad), std::sin(dir_rad));
    sf::Vector2f part_vel = base_vel + burst_vel;
    new_particle.SetVelocity(part_vel.x, part_vel.y);
    new_particle.SetAcceleration(0, 150);
    new_particle.SetInverseMass(1);
    new_particle.SetDamping(0.999);
    new_particle.SetLife(1.0);
    new_particle.SetGenerations(spawn_generations);
    particle_list_.push_back(new_particle);
  }

  return;
}

void ParticleEmitter::Draw(sf::RenderWindow &window) {
  window.draw(object_);
  for (int i = 0; i < particle_list_.size(); i++) {
    window.draw(particle_list_[i].object_);
  }

  return;
}

