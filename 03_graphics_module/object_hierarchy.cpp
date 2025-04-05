#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

class Node {
 public:
  void transform_node(sf::Transform& transform) {
    m_transform = transform;
  }

  void add_child_node(Node* child) {
    m_children.push_back(child);
  }

  void draw(sf::RenderTarget& target, const sf::Transform& parent_transform) const {
    sf::Transform combined_transform = parent_transform * m_transform;
    on_draw(target, combined_transform);
    for (std::size_t i = 0; i < m_children.size(); ++i) {
      m_children[i]->draw(target, combined_transform);
    }
  }

 private:
  virtual void on_draw(sf::RenderTarget& target, const sf::Transform& transform) const = 0;

  sf::Transform m_transform;
  std::vector<Node*> m_children;
};

class CircleNode : public Node {
 public:
  CircleNode(float radius) : m_circle(radius) {
    m_circle.setFillColor(sf::Color(100,250,0));
  }

 private:
  virtual void on_draw(sf::RenderTarget& target, const sf::Transform& transform) const {
    target.draw(m_circle, transform);
  }

  sf::CircleShape m_circle;
};


int main() {
  sf::RenderWindow window(sf::VideoMode(800, 400), "Object Hierarchy Window");

  // Create objects for the object heirarchy
  CircleNode circle0(25.f);
  sf::Transform t0;
  t0.translate(100, 100);
  circle0.transform_node(t0);

  CircleNode circle1(20.f);
  sf::Transform t1;
  t1.translate(-50.f,0);
  circle1.transform_node(t1);
  circle0.add_child_node(&circle1);

  CircleNode circle2(15.f);
  sf::Transform t2;
  t2.translate(-50.f,0);
  circle2.transform_node(t2);
  circle1.add_child_node(&circle2);

  sf::Transform movement_transform;


  // Event loop
  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::KeyPressed:
          if (event.key.code == sf::Keyboard::Right) {
            movement_transform.translate(1.f, 0);
          } else if (event.key.code == sf::Keyboard::Left) {
            movement_transform.translate(-1.f, 0);
          } else if (event.key.code == sf::Keyboard::Down) {
            movement_transform.translate(0, 1.f);
          } else if (event.key.code == sf::Keyboard::Up) {
            movement_transform.translate(0, -1.f);
          }
        default:
          break;
      }
    }

    // draw object hierarchy
    window.clear();
    circle0.draw(window, movement_transform);
    window.display();
  }


  return 0;
}

