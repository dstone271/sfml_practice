#include <SFML/System.hpp>
#include <iostream>

int main()
{
  sf::Time t1 = sf::microseconds(10000);
  sf::Time t2 = sf::milliseconds(10);
  sf::Time t3 = sf::seconds(0.01f);

  std::cout << "Compare micro to milli: " << (t1 == t2) << std::endl;

  sf::Int64 usec = t2.asMicroseconds();
  std::cout << "t2 as usec: " << usec << std::endl;


  sf::Time t4 = t2 * 10.0f;
  std::cout << "time calc sec: " << t4.asSeconds() << std::endl;
  std::cout << "greater than 0.09 sec? " << (t4 > sf::seconds(0.09)) << std::endl;

  sf::Clock clock;
  std::cout << "clock duration: " << clock.getElapsedTime().asSeconds() << std::endl;
  clock.restart();
  for (int i=0; i<10; i++) {
    sf::Time elapsed = clock.restart();
    std::cout << "elapsed time: " << elapsed.asSeconds() << std::endl;
  }


  return 0;
}
