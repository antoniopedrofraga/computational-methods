#include <iostream>
#include "solver/methods/analytical.h"

int main() {
	
	Wall wall(0.01);

	Analytical analytical(wall);
	analytical.compute_solution();

	return 0;
}