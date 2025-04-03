#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


int main()
{
  // Render Window
  sf::RenderWindow my_render_window(sf::VideoMode(800,600), "Render Window");

  // Render Texture
  sf::RenderTexture renderTexture;
  renderTexture.create(500, 500);
  renderTexture.clear(sf::Color::Blue);
  //renderTexture.draw(...)
  renderTexture.display();
  const sf::Texture& texture = renderTexture.getTexture();
  sf::Sprite sprite(texture);

  while (my_render_window.isOpen())
  {
    sf::Event event;

    while (my_render_window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        my_render_window.close();
    }

    // Clear window
    my_render_window.clear(sf::Color::Black);

    // Draw stuff
    my_render_window.draw(sprite);

    // Display to window
    my_render_window.display();
  }

  return 0;
}

