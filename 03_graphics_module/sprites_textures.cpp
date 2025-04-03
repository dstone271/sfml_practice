#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 600), "Sprite Window");

  sf::Texture smile_texture;
  if (!smile_texture.loadFromFile("smile.jpg", sf::IntRect(90,60,550,250)))
  {
    return 0;
  }
  //smile_texture.update(...)
  smile_texture.setSmooth(true);
  smile_texture.setRepeated(true);

  // Create Sprite
  sf::Sprite sprite1;
  sprite1.setTexture(smile_texture);
  sprite1.setTextureRect(sf::IntRect(0,0,250,250));
  sf::Sprite sprite2;
  sprite2.setTexture(smile_texture);
  sprite2.setTextureRect(sf::IntRect(300,0,250,250));
  sprite2.setColor(sf::Color(255,255,255,128));
  sprite2.setPosition(sf::Vector2f(400.f,0.f));

  // Window loop
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
            sprite2.rotate(-1.f);
          } else if (event.key.code == sf::Keyboard::Right) {
            sprite2.rotate(1.f);
          }
        default:
          break;
      }
    }

    window.clear(sf::Color::Black);
    window.draw(sprite1);
    window.draw(sprite2);
    window.display();
  }

  return 0;
}

