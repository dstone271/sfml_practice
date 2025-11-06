#include <iostream>

#include "application.h"


int main() {
  Application app;
  /*if (!app.CreateEntities()) {
    std::cout << "Application entity creation falied" << std::endl;
    return 1;
  }
  */

  app.SetupParticleDemo();
  app.RunGameLoop();

  return 0;
}
