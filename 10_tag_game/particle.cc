#include "particle.h"


void Particle::Integrate(sf::Time elapsed_time) {
  if (inverse_mass_ <= 0.0f) {
    return;
  }

  position_ += velocity_ * elapsed_time.asSeconds();
  sf::Vector2f frame_accel = acceleration_;
  frame_accel += inverse_mass_ * force_accum_;
  velocity_ += frame_accel * elapsed_time.asSeconds();
  velocity_ *= (float)pow(damping_, elapsed_time.asSeconds());

  object_.setPosition(position_);
  ClearForceAccum();

  life_ -= elapsed_time.asSeconds();
} 

void Particle::SetPosition(float x_val, float y_val) {
  position_.x = x_val;
  position_.y = y_val;
}

void Particle::SetVelocity(float x_val, float y_val) {
  velocity_.x = x_val;
  velocity_.y = y_val;
}

void Particle::SetAcceleration(float x_val, float y_val) {
  acceleration_.x = x_val;
  acceleration_.y = y_val;
}

void Particle::SetInverseMass(float inverse_mass) {
  inverse_mass_ = inverse_mass;
}

void Particle::SetDamping(float damping) {
  damping_ = damping;
}

sf::Vector2f Particle::GetPosition() {
  return position_;
}

sf::Vector2f Particle::GetVelocity() {
  return velocity_;
}

void Particle::AddForce(sf::Vector2f force) {
  force_accum_ += force;
}

void Particle::ClearForceAccum() {
  force_accum_.x = 0;
  force_accum_.y = 0;
}

void Particle::SetLife(float life_val) {
  life_ = life_val;
}

float Particle::GetLife() {
  return life_;
}

void Particle::SetGenerations(int generation_val) {
  spawn_generations_ = generation_val;
}

int Particle::GetGenerations() {
  return spawn_generations_;
}

