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

  void AddForce(sf::Vector2f force);
  void ClearForceAccum();

 private:
  sf::Vector2f position_ {};
  sf::Vector2f velocity_ {};
  
  sf::Vector2f force_accum_ {};
  sf::Vector2f acceleration_ {};

  float inverse_mass_ {};
  float damping_ {};

 public:
  sf::CircleShape object_ {5};
};

#endif // PARTICLE_H
