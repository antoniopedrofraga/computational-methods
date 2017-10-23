#ifndef METHOD_H  // include guard
#define METHOD_H

#include "../variants/wall.h" // declare the wall structure


/**
*  A Method class to structure information used to solve the problem
*
* The Method class provides:
* \n-basic constructors for creating a Method object.
* \n-acessor methods to retrieve valuable information
* \n-mutator methods to change the wall grid system
*/
class Method {
protected:
	Wall wall; /**< Private Wall wall. Space step of the solution. */
	std::string name; /**< Private string name. Name of the method. */
public:
	// CONSTRUCTORS

	/**
	* Default constructor.  Intialize a Method object
	* @see Matrix(int Nrows, int Ncols)
	* @see Matrix(const Matrix& m)
	*/
	Method();

	/**
	* Alternate constructor. Initializes a Method with a given parabolic problem.
	* @see Matrix(int Nrows, int Ncols)
	* @see Matrix(const Matrix& m)
	*/
	Method(Wall wall);
	std::string get_name();
	Matrix get_grid();
	virtual void compute_solution() = 0;
};

#endif