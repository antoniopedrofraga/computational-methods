#ifndef UTILS_H  // include guard
#define UTILS_H

#include <cmath> // PI calculation
#include <string> // string usage

const double DELTA_T = 0.01; /**< Macro double. The default time step. */
const double DELTA_X = 0.05; /**< Macro double. The default space step. */

const double DIFUSIVITY = 0.1; /**< Macro double. The default value of difusivity. */
const double THICKNESS = 1.0; /**< Macro double. The default value of thickness. */
const double TIMELIMIT = 0.5; /**< Macro double. The default value of time limit. */

const double SURFACE_TEMPERATURE = 300.0; /**< Macro double. The default surface temperature. */
const double INITIAL_TEMPERATURE = 100.0; /**< Macro double. The default initial temperature. */

const double NUMBER_TIME_STEPS = 6.0; /**< Macro double. The default limit of time steps. 0, 0.1, 0.2, 0.3, 0.4, 0.5 */
const unsigned int NUMBER_OF_EXPANSIONS = 20; /**< Macro unsigned int. Number of expansions to calculate the analytical solution sum expansion. */

const double PI = std::atan(1) * 4; /**< Macro double. Approximated value of PI. */

const std::string PLOTS_PATH = "../plots"; /**< Macro string. Default plot exporting path. */

#endif