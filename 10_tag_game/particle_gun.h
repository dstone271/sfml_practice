#ifndef PARTICLE_GUN_H
#define PARTICLE_GUN_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "particle.h"
#include "utility.h"
#include "control_input.h"


class ParticleGun {
 public:
  sf::RectangleShape object_ {};

  void Update(const ControlInput &input, sf::Time elapsed_time);
  void SetPosition(float x_val, float y_val);
  void SetVelocity(float x_val, float y_val);
  void SetOrientation(float x_val, float y_val);
  void SetSize(float x_val, float y_val);
  void Draw(sf::RenderWindow &window);
  int GetNumParticles();
  sf::Vector2f GetParticlePos(int index);

 private:
  sf::Vector2f position_ {};
  sf::Vector2f velocity_ {};
  float max_speed_ {200};
  float rotation_speed_ {90};
  float particle_speed_ {600};
  sf::Vector2f orientation_ {};
  std::vector<Particle> particle_list_ {};
};

#endif // PARTICLE_GUN_H
