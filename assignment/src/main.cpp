#include <iostream>
#include "methods/analytical.h"
#include "methods/explicit/dufort_frankel.h"
#include "methods/explicit/richardson.h"
#include "methods/implicit/laasonen.h"
#include "methods/implicit/crank_nicolson.h"

int main() {

	Wall wall(0.01);
	wall.set_initial_conditions();

	Analytical analytical(wall);
	analytical.compute_solution();

	DufortFrankel dufort_frankel(wall);
	dufort_frankel.compute_solution();

	Richardson richardson(wall);
	richardson.compute_solution();

	Laasonen laasonen(wall);
	laasonen.compute_solution();

	CrankNicolson crank_nicolson(wall);
	crank_nicolson.compute_solution();
	
	return 0;
}