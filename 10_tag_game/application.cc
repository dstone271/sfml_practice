#include "application.h"


bool Application::CreateEntities() {
  window_.create(sf::VideoMode(800, 800), "TAG Game");
  if (!character_texture_.loadFromFile("smile.jpg")) {
    std::cout << "Error: failed to load texture" << std::endl;
    return false;
  }
  character_.object_.setTexture(character_texture_);
  character_.object_.setTextureRect(sf::IntRect(85, 60, 240, 240));
  character_.object_.setOrigin(120, 120);
  character_.object_.setScale(0.5f, 0.5f);
  character_.position_ = sf::Vector2f(80, 80);
  character_.size_ = sf::Vector2f(120, 120);
  character_.orientation_ = sf::Vector2f(1, 0);

  // Create collidable objects and add to list
  //collidable_list_.CreateNewObject(sf::Vector2f(200, 200), sf::Vector2f(200, 50), sf::Vector2f(1, 0));
  //collidable_list_.CreateNewObject(sf::Vector2f(100, 400), sf::Vector2f(300, 50), sf::Vector2f(0.866, 0.5));
  collidable_list_.CreateNewObject(sf::Vector2f(600, 200), sf::Vector2f(50, 300), sf::Vector2f(1,0)); //sf::Vector2f(0.7071, 0.7071));
  //collidable_list_.CreateNewObject(sf::Vector2f(500, 500), sf::Vector2f(100, 100), sf::Vector2f(0.5, 0.866));

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
      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Num1) {
          character_.control_type_ = ControlType::instant_accel;
        } else if (event.key.code == sf::Keyboard::Num2) {
          character_.control_type_ = ControlType::constant_accel;
        } else if (event.key.code == sf::Keyboard::Num3) {
          character_.control_type_ = ControlType::proportional_accel;
        }
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

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    input_.rotation_direction_ = RotationDirection::counter_clockwise;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    input_.rotation_direction_ = RotationDirection::clockwise;
  } else {
    input_.rotation_direction_ = RotationDirection::no_rotation;
  }
}


void Application::UpdateState() {
  elapsed_time_ = clock_.getElapsedTime();
  clock_.restart();

  UpdateControllableObject(character_, input_, elapsed_time_);
  CheckAndResolveCollisions(character_, collidable_list_);
}


void Application::RenderGraphics() {
  window_.clear();
  window_.draw(character_.object_);
  for (int i=0; i<collidable_list_.GetSize(); i++) {
    window_.draw(collidable_list_.GetObject(i).object_);
  }
  window_.display();
}

