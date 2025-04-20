#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;

sf::Vector2f get_unit_direction(const sf::Vector2f& direction) {
  sf::Vector2f unit_direction(0.f, 0.f);

  float magnitude = direction.x * direction.x;
  magnitude += direction.y * direction.y;
  magnitude = sqrt(magnitude);

  if (magnitude == 0) {
    return unit_direction;
  } else {
    unit_direction = direction / magnitude;
    return unit_direction;
  }
}


int main() {
  sf::RenderWindow window(sf::VideoMode(800, 800), "TAG Game");
  sf::Texture smile_texture;
  if (!smile_texture.loadFromFile("smile.jpg")) {
    cout << "Error: failed to load smile texture" << endl;
    return 0;
  }
  sf::Sprite character;
  character.setTexture(smile_texture);
  character.setTextureRect(sf::IntRect(85, 60, 240, 240));
  character.setScale(0.5f, 0.5f);

  // Physical state
  sf::Vector2f position(0, 0);
  sf::Vector2f vel_direction(0, 0);
  float max_speed = 100;

  // System info
  sf::Time elapsed_time;
  sf::Clock clock;

  while (window.isOpen()) {
    sf::Event event;
    elapsed_time = clock.getElapsedTime();
    clock.restart();

    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;
        default:
          break;
      }
    }

    // Process control input
    vel_direction = sf::Vector2f(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      vel_direction.x -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      vel_direction.x += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      vel_direction.y -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      vel_direction.y += 1;
    }

    // Calculate Position from velocity
    sf::Vector2f frame_vel = get_unit_direction(vel_direction) * max_speed * elapsed_time.asSeconds();
    position = position + frame_vel;
    character.setPosition(position);

    window.clear();
    window.draw(character);
    window.display();
  }

  return 0;
}
