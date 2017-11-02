#include "method.h"

// CONSTRUCTORS
/*=
 *Default constructor
 */
Method::Method() {}

/*
 * Alternate constructor - creates a method with a given problem
 */
Method::Method(Problem problem) {
	this->problem = problem;
}

// PUBLIC ACCESSOR METHODS

/*
 * public accessor method - get the method name
 */
std::string Method::get_name() {
	return name;
}

/*
 * public accessor method - get the solution grid
 */
Matrix Method::get_solution() {
	return (*problem.get_solution());
}

/*
 * public accessor method - get the solution time step
 */
double Method::get_deltat() {
	return problem.get_deltat();
}

/*
 * public accessor method - get x values vector
 */
Vector Method::get_xvalues() {
	return problem.get_xvalues();
}

void Method::compute() {
	clock_t begin = clock();
	compute_solution();
	clock_t end = clock();
	time = double(end - begin) * 1000 / CLOCKS_PER_SEC;
}

