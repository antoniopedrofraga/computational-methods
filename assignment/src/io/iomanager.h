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
	std::string output_path;  /**< Private string output_path. Contains the ouput directory path name. */

	// PRIVATE PLOT METHODS

	/**
	* Method to create ouput folder if the folder does not exist
	* @return bool. true if successfull, false if not
	*/
	bool create_output_dir();

	/**
	* Exports a plot that compares the analytical solution to any other solution using gnuplot
	* @param string output_name File name to be exported
	* @param Method* analytical The analytical solution
	* @param Method* method Any method solution
	*/
	void plot(std::string output_name, Method * analytical, Method * method);

	/**
	* Exports an error table to a .lsx file that compares the analytical solution to any other solution
	* @param string output_name File name to be exported
	* @param Method* analytical The analytical solution
	* @param Method* method Any method solution
	*/
	void error_table(std::string output_name, Method * analytical, Method * method);

	// AUX METHODS

	/**
	* Converts a double to a string with a precison of 2 decimal places
	* @param double value Number to be converted
	* @return string. String containing the converted number
	*/
	std::string double_to_string(int precision, double value);
public:
	// CONSTRUCTORS

	/**
	* Default constructor.  Initialize an IOManager object.
	*/
	IOManager();

	// PUBLIC OUTPUTS METHODS

	/**
	* Exports outputs regarding plots images and error tables for each computed solution, comparing them to the analytical solution
	* @param Method* analytical The analytical solution
	* @param vector<Method*> methods Vector containing the solutions 
	*/
	void export_outputs(Method * analytical, std::vector<Method*> methods);
};

#endif