#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;
extern Sprocket sprockets;

inline pros::Optical opticalSensor(1);
inline ez::Piston matchLoaderPiston('A');
inline ez::Piston hoodPiston('B');

inline pros::Motor sprocketBottom(19);
inline pros::Motor sprocketTop(18);
inline pros::Motor sprocketIndexer(20);

inline enum class Team {RED, BLUE, SKILLS} team;
