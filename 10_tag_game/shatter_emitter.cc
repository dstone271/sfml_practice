#include "shatter_emitter.h"


void ShatterEmitter::Update(sf::Time elapsed_time) {
  if (active_) {
    // Update Particles
    for (int i = 0; i < particle_list_.size(); i++) {
      Particle &current_particle = particle_list_[i];
      current_particle.Integrate(elapsed_time);
      if (current_particle.GetLife() <= 0.0) {
        particle_list_.erase(particle_list_.begin() + i);
      }
    }

    if (particle_list_.size() == 0) {
      active_ = false;
    }
  }

  return;
}


void ShatterEmitter::Draw(sf::RenderWindow &window) {
  for (int i = 0; i < particle_list_.size(); i++) {
    window.draw(particle_list_[i].object_);
  }

  return;
}


void ShatterEmitter::Activate(sf::Vector2f box_position, sf::Vector2f box_size) {
  if (active_ == true) {
    return;
  }
  active_ = true;

  float box_width = box_size.x;
  float box_height = box_size.y;
  sf::Vector2f box_corner = box_position - (box_size / 2.f);

  for (int i = 0; i < num_height_segments_; i++) {
    for (int j = 0; j < num_width_segments_; j++) {
      Particle new_particle;
      float pos_x = box_corner.x + (box_width * (2.0 * i + 1)) / (2.0 * num_width_segments_);
      float pos_y = box_corner.y + (box_height * (2.0 * j + 1)) / (2.0 * num_height_segments_);
      new_particle.SetPosition(pos_x, pos_y);
      sf::Vector2f direction = min_speed_ * (new_particle.GetPosition() - box_position);
      direction.x += (((float) std::rand() / static_cast<float>(RAND_MAX)) - 0.5) * 100;
      direction.y += (((float) std::rand() / static_cast<float>(RAND_MAX)) - 0.5) * 100;
      new_particle.SetVelocity(direction.x, direction.y);
      new_particle.SetAcceleration(0, 120);
      new_particle.SetInverseMass(1);
      new_particle.SetDamping(0.15);
      new_particle.SetLife(1.5);
      new_particle.object_.setFillColor(sf::Color(255, 100, 50, 255));
      new_particle.object_.setTexture(&particle_texture_);
      particle_list_.push_back(new_particle);
    }
  }

  return;
}


bool ShatterEmitter::IsActive() {
  return active_;
}
