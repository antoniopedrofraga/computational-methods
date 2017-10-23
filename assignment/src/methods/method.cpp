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
Matrix Method::get_grid() {
	return (*problem.get_grid());
}
