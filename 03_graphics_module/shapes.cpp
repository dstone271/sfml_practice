#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class CustomShape : public sf::Shape
{
 public:
  explicit CustomShape(int size) : m_size(size)
  {
    update();
  }

  void setSize(int size)
  {
    m_size = size;
    update();
  }

  virtual std::size_t getPointCount() const
  {
    return 4;
  }

  virtual sf::Vector2f getPoint(std::size_t index) const
  {
    return sf::Vector2f(m_size * (index%2), m_size * (index/2));
  }
 
 private:
  int m_size;
};

int main()
{
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::RenderWindow window(sf::VideoMode(800,400), "shapes window", sf::Style::Default, settings);

  sf::Texture wood_texture;
  wood_texture.loadFromFile("wood.jpg");

  // Shape Properties
  sf::CircleShape shape(50.f);
  shape.setPosition(sf::Vector2f(0,0));
  shape.setFillColor(sf::Color(100, 250, 50));
  shape.setOutlineThickness(-10.f);
  shape.setOutlineColor(sf::Color(250,150,100));
  shape.setTexture(&wood_texture);
  shape.setTextureRect(sf::IntRect(10,10,10,10));

  // Rectangles
  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(80.f, 40.f));
  rectangle.setPosition(sf::Vector2f(200, 10));

  // Circle and Regular Polygons
  sf::CircleShape triangle;
  triangle.setRadius(40.f);
  triangle.setPointCount(3);
  triangle.setPosition(sf::Vector2f(10,100));

  sf::CircleShape diamond(40.f, 4);
  diamond.setPosition(sf::Vector2f(100,100));

  sf::CircleShape octagon(40.f, 8);
  octagon.setPosition(sf::Vector2f(200,100));

  sf::ConvexShape star;
  star.setPosition(sf::Vector2f(10,200));
  star.setPointCount(10);
  star.setPoint(0, sf::Vector2f(50.f,0.f));
  star.setPoint(1, sf::Vector2f(60.f,25.f));
  star.setPoint(2, sf::Vector2f(90.f,25.f));
  star.setPoint(3, sf::Vector2f(65.f,55.f));
  star.setPoint(4, sf::Vector2f(80.f,90.f));
  star.setPoint(5, sf::Vector2f(50.f,65.f));
  star.setPoint(6, sf::Vector2f(20.f,90.f));
  star.setPoint(7, sf::Vector2f(35.f,55.f));
  star.setPoint(8, sf::Vector2f(10.f,25.f));
  star.setPoint(9, sf::Vector2f(40.f,25.f));

  // Custom Shape
  int box_size = 100;
  CustomShape sized_box(box_size);
  sized_box.setPosition(sf::Vector2f(400.f, 10.f));

  while (window.isOpen())
  {
    sf::Event event;

    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        //window.close();
        box_size++;
        sized_box.setSize(box_size);
      }
    }

    window.clear();
    window.draw(shape);
    window.draw(rectangle);
    window.draw(triangle);
    window.draw(diamond);
    window.draw(octagon);
    window.draw(star);
    window.draw(sized_box);
    window.display();
  }

  return 0;
}
