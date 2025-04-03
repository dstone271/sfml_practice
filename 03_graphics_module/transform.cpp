#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
  sf::RenderWindow window(sf::VideoMode(800,400), "transform window");

  sf::RectangleShape shape(sf::Vector2f(200,150));
  shape.setFillColor(sf::Color::Green);

  // Custom Transforms
  sf::RectangleShape rect1(sf::Vector2f(100,80));
  sf::RectangleShape rect2(sf::Vector2f(200,160));
  sf::Transform t1;
  t1.translate(20, 0);
  t1.rotate(45);
  t1.translate(100,0);
  t1.scale(0.5, 0.5);
  sf::Transform t2(2, 0, 20,
                   0, 1, 50,
                   0, 0, 1);
  sf::Transform t3 = t2 * t1;
  sf::Transform t4 = sf::Transform::Identity;
  sf::Transform t5 = shape.getTransform();

  // Bounding Boxes
  sf::FloatRect boundingBox;

  while (window.isOpen())
  {
    sf::Event event;

    while (window.pollEvent(event))
    {
      switch (event.type)
      {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::KeyPressed:
          if (event.key.code == sf::Keyboard::Left) {
            shape.move(sf::Vector2f(-1,0));
          } else if (event.key.code == sf::Keyboard::Right) {
            shape.move(sf::Vector2f(1,0));
          } else if (event.key.code == sf::Keyboard::Up) {
            shape.move(sf::Vector2f(0,-1));
          } else if (event.key.code == sf::Keyboard::Down) {
            shape.move(sf::Vector2f(0,1));
          } else if (event.key.code == sf::Keyboard::R) {
            shape.rotate(1);
          } else if (event.key.code == sf::Keyboard::O) {
            sf::Vector2f origin = shape.getOrigin();
            if (origin.x != 0) {
              shape.setOrigin(0,0);
            } else {
              shape.setOrigin(100,75);
            }
          } else if (event.key.code == sf::Keyboard::S) {
            shape.scale(1.1,1.1);
          } else if (event.key.code == sf::Keyboard::Q) {
            shape.setPosition(sf::Vector2f(0,0));
            shape.setRotation(0);
            shape.setScale(1,1);
            shape.setOrigin(0,0);
          }
          break;

        default:
          break;
      }
    }

    // Bounding Box
    boundingBox = shape.getGlobalBounds();
    if (boundingBox.contains(sf::Vector2f(200,200))) {
      std::cout << "Hit point" << std::endl;
    }

    window.clear();
    window.draw(shape);
    window.draw(rect1, t1);
    window.draw(rect1, t3);
    window.display();
  }

  return 0;
}
