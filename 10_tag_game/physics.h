#ifndef PHYSICS_H
#define PHYSICS_H

#include <SFML/System.hpp>

#include "controllable_object.h"
#include "control_input.h"


void UpdateControllableObject(ControllableObject& object, const ControlInput& input, sf::Time elapsed_time); 

#endif // PHYSICS_H
