#include "dufort_frankel.h"

DufortFrankel::DufortFrankel(Wall wall)
: Method(wall) {}

void DufortFrankel::compute_solution() {
	Matrix * grid = wall.get_grid();
	Vector current_iteration(wall.get_xsize() + 1), temp(wall.get_xsize() + 1);
	/*for ()
	f[1][i] = f[n - 1][i] - A * DELTAT * (f[n - 1][i] - f[n - 1][i - 1]) / DELTAX;
	*/
	/* use upwind on first iteration */
}