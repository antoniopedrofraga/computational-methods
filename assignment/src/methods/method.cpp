#include "method.h"

// CONSTRUCTORS
/*=
 *Default constructor
 */
Method::Method() {}

/*
 * Alternate constructor - creates a method with a given problem
 */
Method::Method(Wall wall) {
	this->wall = wall;
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
	return (*wall.get_grid());
}
