#ifndef IO_MANAGER_H  //Include guard
#define IO_MANAGER_H

#include "../libs/gnuplot-iostream.h" // lib to be able to use gnuplot from c++
#include "../methods/method.h" // provides knowledge about method objects structure

/**
*  An input/output manager class to handle plot exportations and future implementations of input handling
*
* The IOManager class provides:
* \n-plot method which compares the analytical solution with a set of given methods, ploting them with a custom configuration using gnuplot
*/
class IOManager {
private:
	std::string plots_path;  /**< Private string plots_path. Contains the plots directory path name. */

	// PLOT METHODS

	/**
	* Method to create plots folder if the folder does not exist
	* @return bool. true if successfull, false if not
	*/
	bool create_plots_dir();

	/**
	* Exports a plot that compares the analytical solution to any other solution wsing gnuplot
	* @param Method* analytical The analytical solution
	* @param Method* method Any method solution
	*/
	void plot(Method * analytical, Method * method);

	// AUX METHODS

	/**
	* Converts a double to a string with a precison of 2 decimal places
	* @param double value Number to be converted
	* @return string. String containing the converted number
	*/
	std::string double_to_string(double value);
public:
	// CONSTRUCTORS

	/**
	* Default constructor.  Initialize an IOManager object.
	*/
	IOManager();

	// PLOT METHODS

	/**
	* Exports one plot for each computed solution, comparing them to the analytical solution
	* @param Method* analytical The analytical solution
	* @param vector<Method*> methods Vector containing the solutions to be plotted
	*/
	void export_plots(Method * analytical, std::vector<Method*> methods);
};

#endif