#include <SFML/Window.hpp>

int main()
{
  // Main window
  sf::Window window(sf::VideoMode(800,600), "My Window");
  // I think these next two functions just control the framerate for drawing,
  // but not with code execution
  //window.setVerticalSyncEnabled(true);
  //window.setFramerateLimit(2);
  window.setTitle("My *Cool* Window");

  // Second window
  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
  sf::VideoMode my_mode;
  my_mode.width = 400;
  my_mode.height = 300;
  my_mode.bitsPerPixel = desktop.bitsPerPixel;
  sf::Window small_window;
  //small_window.create(my_mode, "Small window", sf::Style::Titlebar | sf::Style::Close);
  small_window.create(my_mode, "Small window splash", sf::Style::None);
  small_window.setPosition(sf::Vector2i(400, 200));
  small_window.setSize(sf::Vector2u(600, 450));

  // Main loop
  while (window.isOpen())
  {
    // check window events
    sf::Event event;
    while (window.pollEvent(event))
    {
      bool focus = window.hasFocus();

      if (event.type == sf::Event::Closed)
        window.close();
    }

    // check small window events
    while (small_window.pollEvent(event)) {}

  }


  return 0;
}
