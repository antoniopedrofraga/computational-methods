#include <iostream>
#include "methods/analytical.h"
#include "methods/explicit/dufort_frankel.h"
#include "methods/explicit/richardson.h"
#include "methods/implicit/laasonen.h"
#include "methods/implicit/crank_nicolson.h"
#include "io/iomanager.h"

int main() {
	IOManager io_manager;
	Problem problem(DELTA_T, DELTA_X);
	Analytical analytical(problem);
	DufortFrankel dufort_frankel(problem);
	Richardson richardson(problem);
	Laasonen laasonen(problem);
	CrankNicolson crank_nicolson(problem);
	std::vector<Method*> solutions = {&analytical, &dufort_frankel, &richardson, &laasonen, &crank_nicolson};

	for (int index = 0; index < solutions.size(); index++) {
		solutions[index]->compute_solution();
	}

	std::vector<Method*> methods(solutions.begin() + 1, solutions.end());
	io_manager.export_plots(solutions[0], methods);

	return 0;
}