#ifndef SHATTER_EMITTER_H
#define SHATTER_EMITTER_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>

#include "particle.h"


class ShatterEmitter {
 public:
  void Update(sf::Time elapsed_time);
  void Draw(sf::RenderWindow &window);
  void Activate(sf::Vector2f box_position, sf::Vector2f box_size);
  bool IsActive();

 private:
  int num_width_segments_ {14};
  int num_height_segments_ {14};
  float min_speed_ {10};
  float max_speed_ {300};
  float percent_collision_velocity_ {0.5};
  bool active_ {false};
  std::vector<Particle> particle_list_ {};

 public:
  sf::Texture particle_texture_ {};
};

#endif // SHATTER_EMITTER_H
