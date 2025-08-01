#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;
extern Sprocket sprockets;

inline ez::Piston matchLoaderPiston('H'); 
inline ez::Piston hoodPiston('G');

inline pros::Motor sprocketBottom(19);
inline pros::Motor sprocketTop(18);
inline pros::Motor sprocketIndexer(20);
