#include <iostream>
#include "methods/analytical.h"
#include "methods/dufort_frankel.h"
#include "methods/richardson.h"

int main() {

	Wall wall(0.01);
	wall.set_initial_conditions();

	Analytical analytical(wall);
	analytical.compute_solution();

	DufortFrankel dufort_frankel(wall);
	dufort_frankel.compute_solution();

	Richardson richardson(wall);
	richardson.compute_solution();

	return 0;
}