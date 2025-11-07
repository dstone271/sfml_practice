#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>


class Particle {
 public:
  void Integrate(sf::Time elapsed_time);

  void SetPosition(float x_val, float y_val);
  void SetVelocity(float x_val, float y_val);
  void SetAcceleration(float x_val, float y_val);
  void SetInverseMass(float inverse_mass);
  void SetDamping(float damping);

  sf::Vector2f GetPosition();
  sf::Vector2f GetVelocity();

  void AddForce(sf::Vector2f force);
  void ClearForceAccum();

  void SetLife(float life_val);
  float GetLife();
  void SetGenerations(int generation_val);
  int GetGenerations();

 private:
  sf::Vector2f position_ {};
  sf::Vector2f velocity_ {};
  
  sf::Vector2f force_accum_ {};
  sf::Vector2f acceleration_ {};

  float inverse_mass_ {};
  float damping_ {};

  float life_ {};
  int spawn_generations_ {};

 public:
  sf::CircleShape object_ {5};
};

#endif // PARTICLE_H
