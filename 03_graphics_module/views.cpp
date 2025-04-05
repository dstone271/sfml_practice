#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Views Window");
  
  // Create textured sprite for background
  sf::Texture smile_texture;
  if (!smile_texture.loadFromFile("smile.jpg")) {
    return 0;
  }
  sf::Vector2u texture_size = smile_texture.getSize();
  cout << "Texture size.  x: " << texture_size.x << ", y: " << texture_size.y << endl;
  smile_texture.setRepeated(true);
  sf::Sprite background_sprite;
  background_sprite.setTexture(smile_texture);
  background_sprite.setTextureRect(sf::IntRect(0, 0, 800, 600));

  // Create main view
  sf::View main_view;
  sf::Vector2f view_center(100,100);
  main_view.setCenter(view_center);
  main_view.setSize(sf::Vector2f(100, 100));

  //Create mini map view
  sf::View map_view;
  map_view.reset(sf::FloatRect(0, 0, 800, 600));
  map_view.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));

  // Box to highlight view area
  sf::RectangleShape highlight_box;
  highlight_box.setOutlineThickness(-5.f);
  highlight_box.setOutlineColor(sf::Color::Black);
  highlight_box.setFillColor(sf::Color::Transparent);
  highlight_box.setSize(sf::Vector2f(100, 100));
  highlight_box.setPosition(view_center - sf::Vector2f(50, 50));

  // Map pixel coordniates to world coordinates
  window.setView(main_view);
  sf::Vector2i pixel_pos = sf::Mouse::getPosition(window);
  sf::Vector2f world_pos = window.mapPixelToCoords(pixel_pos);
  cout << "Mouse position in world.  x: " << world_pos.x << ", y: " << world_pos.y << endl;

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      switch(event.type) {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::KeyPressed:
          if (event.key.code == sf::Keyboard::Right) {
            main_view.move(5, 0);
          } else if (event.key.code == sf::Keyboard::Left) {
            main_view.move(-5, 0);
          } else if (event.key.code == sf::Keyboard::Down) {
            main_view.move(0, 5);
          } else if (event.key.code == sf::Keyboard::Up) {
            main_view.move(0, -5);
          }
          view_center = main_view.getCenter();
          highlight_box.setPosition(view_center - sf::Vector2f(50, 50));
          break;
        case sf::Event::MouseButtonPressed:
          // Map pixel coordinates to world coordinates
          window.setView(main_view);
          pixel_pos = sf::Mouse::getPosition(window);
          world_pos = window.mapPixelToCoords(pixel_pos);
          cout << "Mouse position in world.  x: " << world_pos.x << ", y: " << world_pos.y << endl;
          break;
        default:
          break;
      }
    }

    window.clear();
    window.setView(main_view);
    window.draw(background_sprite);
    window.setView(map_view);
    window.draw(background_sprite);
    window.draw(highlight_box);
    window.display();
  }

  return 0;
}
