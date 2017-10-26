#include "iomanager.h"

// CONSTRUCTORS
/*=
 * Default constructor
 */

IOManager::IOManager() {
	plots_path = PLOTS_PATH;
}

// PLOT METHODS

/*
* private plot method - creates plots folder 
*/

bool IOManager::create_plots_dir() {
	char answer = '.';

	// if plot folder exists ask if the user wants to replace the previous results
	if(boost::filesystem::exists(plots_path)) {
		while (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N') {
			std::cout << "Plots folder already exists, this program might overwrite some files, procceed? [Y:N] - ";
			answer = std::getchar();
			std::cout << std::endl;
		}
		return answer == 'y' || answer == 'Y' ? true : false;
	} else {
		if(boost::filesystem::create_directory(plots_path)) {
			std::cout << "Plots folder was created!" << std::endl;
			return true;
		} else {
			std::cout << "Plots folder couldn't be created! Not exporting plots." << std::endl;
			return false;
		}
	}
}

/*
* public plot method - iterates through all the solutions in order to export them
*/

void IOManager::export_plots(Method * analytical, std::vector<Method*> methods) {
	if (!create_plots_dir()) return;
	std::cout << "Exporting plots to " << boost::filesystem::canonical(plots_path, ".") << std::endl;
	for (unsigned int index = 0; index < methods.size(); index++) {
		std::cout << "Exporting " << (*methods[index]).get_name() << " method plots... ";
		plot(analytical, methods[index]);
		std::cout << "Finished!" << std::endl;
	}
}

/*
* private plot method - Exports a plot chart which compares the analytical solution with a given solution
*/

void IOManager::plot(Method * analytical, Method * method) {
	// Object to export plots
	Gnuplot gp;

	// methods solutions
	Matrix analytical_matrix = analytical->get_solution(), method_matrix = method->get_solution();
	unsigned int rows = method_matrix.getNrows();
	unsigned int cols = method_matrix.getNcols();

	// defining gnuplot configuration with the correct syntax
	gp << "set tics scale 0; set border 3; set ylabel \"ºF\";set xlabel \"x\"; set yrange [90:310]; set term png; set xtics (\"0\" 0, \"0.5\"" << cols / 2 << ", \"1\"" << cols - 1 << ")\n";
	for (unsigned int index = 1; index < rows; index++) {
		double time = (double)index / 10.0;
		std::string name = method->get_name(), time_str = double_to_string(time);
		gp << "set title \"" << name << " method at t = " << time_str << "\";set output \"../plots/" << name << "t="  << time_str << ".png\";\n";
		gp << "plot" << gp.file1d(analytical_matrix[index]) << "with lines title \"Analytical\" lw 2 lt rgb \"red\","
			<< gp.file1d(method_matrix[index]) << "with points title \"" << name << "\" pt 17 ps 1 lw 1" << std::endl;
	}
}

// AUX METHODS

/*
* aux method - Converts a double into a string
*/

std::string IOManager::double_to_string(double value) {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << value;
	return stream.str();
} 