#include "iomanager.h"

// CONSTRUCTORS
/*=
 * Default constructor
 */

IOManager::IOManager() {
	output_path = OUTPUT_PATH;
}

// PLOT METHODS

/*
* private output method - creates output folder 
*/

bool IOManager::create_output_dir() {
	char answer = '.';

	// if plot folder exists ask if the user wants to replace the previous results
	if(boost::filesystem::exists(output_path)) {
		while (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N') {
			std::cout << "Output folder already exists, this program might overwrite some files, procceed? [Y:N] - ";
			answer = std::getchar();
			std::cout << std::endl;
		}
		return answer == 'y' || answer == 'Y' ? true : false;
	} else {
		if(boost::filesystem::create_directory(output_path)) {
			std::cout << "Output folder was created!" << std::endl;
			return true;
		} else {
			std::cout << "Output folder couldn't be created! Not exporting outputs." << std::endl;
			return false;
		}
	}
}

/*
* public output method - iterates through all the solutions in order to export them
*/

void IOManager::export_outputs(Method * analytical, std::vector<Method*> methods) {
	if (!create_output_dir()) return;
	std::cout << "Exporting outputs to " << boost::filesystem::canonical(output_path, ".") << std::endl;
	std::string name, output_name, deltat_string;
	for (unsigned int index = 0; index < methods.size(); index++) {
		name = (*methods[index]).get_name();
		deltat_string = name == LAASONEN ? double_to_string(3, methods[index]->get_deltat()) : double_to_string(2, methods[index]->get_deltat());
		output_name = output_path + '/' + name;
		if (name == LAASONEN) {
			output_name += "dt=" + deltat_string;
		}
		std::cout << "Exporting " << name << " method outputs... ";
		plot(output_name, analytical, methods[index]);
		error_table(output_name, analytical, methods[index]);
		std::cout << "Finished!" << std::endl;
	}
}

/*
* private plot method - Exports a plot chart which compares the analytical solution with a given solution
*/

void IOManager::plot(std::string output_name, Method * analytical, Method * method) {
	// Object to export plots
	Gnuplot gp;

	// methods solutions
	Matrix analytical_matrix = analytical->get_solution(), method_matrix = method->get_solution();
	unsigned int rows = method_matrix.getNrows();
	unsigned int cols = method_matrix.getNcols();
	double time;
	std::string time_str, name = method->get_name();

	// defining gnuplot configuration with the correct syntax
	gp << "set tics scale 0; set border 3; set ylabel \"Temperature [ºF]\";set xlabel \"x [ft]\"; set yrange [90:310]; set term png; set xtics (\"0\" 0, \"0.5\"" << cols / 2 << ", \"1\"" << cols - 1 << ")\n";
	for (unsigned int index = 1; index < rows; index++) {
		time = (double)index / 10.0;
		time_str = double_to_string(1, time);

		gp << "set output \"" << output_name << "t="  << time_str;
		gp << ".png\";\n";
		gp << "plot" << gp.file1d(analytical_matrix[index]) << "with lines title \"Analytical\" lw 2 lt rgb \"red\","
			<< gp.file1d(method_matrix[index]) << "with points title \"" << name << "\" pt 17 ps 1 lw 1" << std::endl;
	}
}

/*
* private table method - Exports an error table to a .lsx file which compares the analytical solution with a given solution
*/
void IOManager::error_table(std::string output_name, Method * analytical, Method * method) {
	std::string name = output_name + ".csv", time, x_str;
	std::ofstream out;

	Matrix analytical_matrix = analytical->get_solution(), method_matrix = method->get_solution();
	Vector x_values = method->get_xvalues();
	unsigned int rows = method_matrix.getNrows();
	unsigned int cols = method_matrix.getNcols();

	out.open(name);
	out << " & ";
	for (int i = 0; i < x_values.getSize(); i++) {
		x_str = double_to_string(2, x_values[i]);
		out << "x=" << x_str << " & ";
	}
	out << '\n';
	for (unsigned int i = 1; i < rows; i++) {
		time = double_to_string(2, (double)i / 10.0);
		out << "t=" << time << " & ";
		for (unsigned int j = 0; j < cols; j++) {
			out << analytical_matrix[i][j] - method_matrix[i][j] << " & ";
		}
		out << '\n';
	}
	out.close();
}

// AUX METHODS

/*
* aux method - Converts a double into a string
*/

std::string IOManager::double_to_string(int precision, double value) {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(precision) << value;
	return stream.str();
} 