#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;
extern Sprocket sprockets;

// inline ez::Piston hopperMechanism(20);

inline pros::Motor sprocketBottom(14);
inline pros::Motor sprocketTop(15);
inline pros::Motor sprocketIndexer(16);
