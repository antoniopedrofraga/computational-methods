#include <iostream>
#include "methods/analytical.h"
#include "methods/dufort_frankel.h"

int main() {

	Wall wall(0.01);

	Analytical analytical(wall);
	analytical.compute_solution();

	DufortFrankel dufort_frankel(wall);
	dufort_frankel.compute_solution();

	return 0;
}