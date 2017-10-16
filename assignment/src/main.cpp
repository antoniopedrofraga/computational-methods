#include <iostream>
#include "methods/analytical.h"
#include "methods/explicit/dufort_frankel.h"
#include "methods/explicit/richardson.h"
#include "methods/implicit/laasonen.h"
#include "methods/implicit/crank_nicolson.h"
#include "io/iomanager.h"

int main() {

	IOManager io_manager;
	Wall wall(0.01);
	Analytical analytical(wall);
	DufortFrankel dufort_frankel(wall);
	Richardson richardson(wall);
	Laasonen laasonen(wall);
	CrankNicolson crank_nicolson(wall);
	std::vector<Method*> solutions = {&analytical, &dufort_frankel, &richardson, &laasonen, &crank_nicolson};

	wall.set_initial_conditions();
	for (int index = 0; index < solutions.size(); index++) {
		solutions[index]->compute_solution();
	}

	std::vector<Method*> methods(solutions.begin() + 1, solutions.end());
	io_manager.export_plots(solutions[0], methods);

	return 0;
}