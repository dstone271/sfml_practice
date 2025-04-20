#include "application.h"


bool Application::CreateEntities() {
  window_.create(sf::VideoMode(800, 800), "TAG Game");
  if (!character_texture_.loadFromFile("smile.jpg")) {
    std::cout << "Error: failed to load texture" << std::endl;
    return false;
  }
  character_.object_.setTexture(character_texture_);
  character_.object_.setTextureRect(sf::IntRect(85, 60, 240, 240));
  character_.object_.setScale(0.5f, 0.5f);
  character_.position_ = sf::Vector2f(0, 0);

  return true;
}


void Application::RunGameLoop() {
  while (window_.isOpen()) {
    ProcessInput();
    UpdateState();
    RenderGraphics();
  }
}


void Application::ProcessInput() {
  sf::Event event;

  while (window_.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        window_.close();
        break;
      default:
        break;
    }
  }

  sf::Vector2f velocity_direction = sf::Vector2f(0, 0);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    velocity_direction.x -= 1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    velocity_direction.x += 1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    velocity_direction.y -= 1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    velocity_direction.y += 1;
  }

  input_.normalized_movement_ = utility::GetUnitDirection(velocity_direction);
}


void Application::UpdateState() {
  elapsed_time_ = clock_.getElapsedTime();
  clock_.restart();

  UpdateControllableObject(character_, input_, elapsed_time_);
}


void Application::RenderGraphics() {
  window_.clear();
  window_.draw(character_.object_);
  window_.display();
}

