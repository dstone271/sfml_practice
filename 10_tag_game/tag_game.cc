#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;


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
  sf::Vector2f velocity(0, 0);

  while (window.isOpen()) {
    sf::Event event;

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
    velocity = sf::Vector2f(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      velocity.x -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      velocity.x += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      velocity.y -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      velocity.y += 1;
    }
    //cout << "Velocity. x: " << velocity.x << ", y: " << velocity.y << endl;
    if (velocity.x == 1) {
      cout << "Position. x: " << position.x << ", y: " << position.y << endl;
    }

    // Calculate Position from velocity
    position = position + velocity;
    character.setPosition(position);

    window.clear();
    window.draw(character);
    window.display();
  }

  return 0;
}
