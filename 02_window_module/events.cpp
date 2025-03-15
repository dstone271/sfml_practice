#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;

int main()
{
  sf::Window window(sf::VideoMode(800, 600), "My Window");
  window.setKeyRepeatEnabled(false);

  // variables
  int resize_num = 0;

  while (window.isOpen())
  {
    sf::Event event;

    while (window.pollEvent(event))
    {
      switch (event.type)
      {
        case sf::Event::Closed:
          cout << "Closed event. " << endl;
          window.close();
          break;
        case sf::Event::Resized:
          cout << "Resized event. ";
          resize_num++;
          cout << "resize #: " << resize_num;
          cout << ", new width: " << event.size.width << ", new height: " << event.size.height;
          cout << endl;
          break;
        case sf::Event::LostFocus:
          cout << "LostFocus event... come back!!!" << endl;
          break;
        case sf::Event::GainedFocus:
          cout << "GainedFocus event... we're back :)" << endl;
          break;
        case sf::Event::TextEntered:
          cout << "TextEntered event. ";
          if (event.text.unicode < 128)
            cout << "char: " << static_cast<char>(event.text.unicode) << ", ";
          cout << "Unicode: " << event.text.unicode << endl;
          break;
        case sf::Event::KeyPressed:
          cout << "KeyPressed event. key code: " << event.key.code;
          if (event.key.code == sf::Keyboard::Escape)
            cout << ", escape key. Shift status: " << event.key.shift;
          cout << endl;
          break;
        case sf::Event::MouseWheelScrolled:
          cout << "MouseWheelScrolled event. ";
          if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            cout << "(wheel type: vertical) ";
          else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
            cout << "(wheel type: horizontal) ";
          else
            cout << "(wheel type: unknown) ";
          cout << "wheel movement: " << event.mouseWheelScroll.delta;
          cout << ", mouse x: " << event.mouseWheelScroll.x;
          cout << ", mouse y: " << event.mouseWheelScroll.y;
          cout << endl;
          break;
        case sf::Event::MouseButtonPressed:
          cout << "MouseButtonPressed event. ";
          cout << "Button code: " << event.mouseButton.button;
          cout << ", mouse x: " << event.mouseButton.x;
          cout << ", mouse y: " << event.mouseButton.y << endl;
          break;
        case sf::Event::MouseButtonReleased:
          cout << "MouseButtonReleased event. ";
          cout << "Button code: " << event.mouseButton.button;
          cout << ", mouse x: " << event.mouseButton.x;
          cout << ", mouse y: " << event.mouseButton.y << endl;
          break;
        case sf::Event::MouseMoved:
          cout << "MouseMoved event. ";
          cout << "mouse x: " << event.mouseMove.x;
          cout << ", mouse y: " << event.mouseMove.y << endl;
          break;
        case sf::Event::MouseEntered:
          cout << "MouseEntered event. " << endl;
          break;
        case sf::Event::MouseLeft:
          cout << "MouseLeft event. " << endl;
          break;
        case sf::Event::JoystickButtonPressed:
          cout << "JoystickButtonPressed event. ";
          cout << "joystick id: " << event.joystickButton.joystickId;
          cout << ", joystick button: " << event.joystickButton.button << endl;
          break;
        case sf::Event::JoystickButtonReleased:
          cout << "JoystickButtonReleased event. ";
          cout << "joystick id: " << event.joystickButton.joystickId;
          cout << ", joystick button: " << event.joystickButton.button << endl;
          break;
        case sf::Event::JoystickMoved:
          cout << "JoystickMoved event. ";
          cout << "joystick id: " << event.joystickMove.joystickId;
          cout << ", joystick axis: " << event.joystickMove.axis;
          // position value is [-100, 100]
          cout << ", new position: " << event.joystickMove.position << endl;
          break;
        case sf::Event::JoystickConnected:
          cout << "JoystickConnected event. ";
          cout << "joystick id: " << event.joystickConnect.joystickId << endl;
          break;
        case sf::Event::JoystickDisconnected:
          cout << "JoystickDisconnected event. ";
          cout << "joystick id: " << event.joystickConnect.joystickId << endl;
          break;

        default:
          break;
      }
    }

  }

  return 0;
}
          
