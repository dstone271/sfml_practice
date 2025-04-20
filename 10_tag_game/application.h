#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "control_input.h"
#include "controllable_object.h"
#include "utility.h"
#include "physics.h"


class Application {
 public:
  bool CreateEntities();
  void RunGameLoop();

 private:
  void ProcessInput();
  void UpdateState();
  void RenderGraphics();

  sf::RenderWindow window_ {};
  sf::Clock clock_ {};
  sf::Time elapsed_time_ {};
  sf::Texture character_texture_ {};
  ControlInput input_ {};
  ControllableObject character_ {};
};

#endif // APPLICATION_H
