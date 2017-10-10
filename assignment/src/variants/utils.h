#ifndef UTILS_H  
#define UTILS_H

#include <cmath>
#include <iostream>

const double DIFUSIVITY = 0.1; /* ft²/hr */
const double THICKNESS = 1.0;
const double TIMELIMIT = 0.5;

const double SURFACE_TEMPERATURE = 300; /* ºF */
const double INITIAL_TEMPERATURE = 100; /* ºF */

const double NUMBER_TIME_STEPS = 6; /* 0, 0.1, 0.2, 0.3, 0.4, 0.5 */
const unsigned int NUMBER_OF_EXPANSIONS = 20;

const double PI = std::atan(1) * 4;

#endif