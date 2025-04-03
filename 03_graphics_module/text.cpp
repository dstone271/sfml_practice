#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

int main()
{
  sf::RenderWindow window(sf::VideoMode(800,600), "text window");

  // Text and Font
  sf::Font font;
  if (!font.loadFromFile("times.ttf"))
    return 0;
  sf::Text text;
  text.setFont(font);
  text.setString("Hello there.");
  text.setCharacterSize(24); // in pixels
  text.setFillColor(sf::Color::Yellow);
  text.setStyle(sf::Text::Bold | sf::Text::Underlined);

  while (window.isOpen())
  {
    sf::Event event;

    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color::Blue);
    window.draw(text);
    window.display();
  }

  return 0;
}
