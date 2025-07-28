#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;
extern Sprocket sprockets;

// inline ez::Piston hopperMechanism(something);

inline pros::Motor sprocketBottom(19);
inline pros::Motor sprocketTop(18);
inline pros::Motor sprocketIndexer(20);
