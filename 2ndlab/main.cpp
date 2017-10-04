#include <iostream>
#include <string>
#include <iomanip>
#include <sstream> 
#include "matrix.h"

const double DELTAX = 0.01;
const double DELTAT = 0.005;
const double XSIZE = 1 / DELTAX;
const double TSIZE = 10 / DELTAT;
const double D = 0.01;
const double PI = std::atan(1)*4;
const double R = (DELTAT * D) / pow(DELTAX, 2);

void solve_analytically(Matrix & matrix, int nsize, Vector & xvalues, Vector & tvalues) {
	for (double x = 0; x <= XSIZE; x++) {
		for (double t = 0; t <= TSIZE; t++) {
			double sum = 0;
			for (double n = 1; n <= nsize; n++) {
				sum += (pow(-1, n) / (PI * n)) * exp(-D * pow(PI, 2) * pow(n, 2) * tvalues[t]) * sin(PI * n * xvalues[x]);
			}
			matrix[t][x] = xvalues[x] + 2 * sum;
		}
	}
}

void simple_excplicit_scheme(Matrix & f) {
	for (int n = 0; n < TSIZE; n++) {
		for (int i = 1; i < XSIZE; i++) {
			f[n + 1][i] = f[n][i] +  R * (f[n][i + 1] - 2 * f[n][i] + f[n][i - 1]);
		}
	}
}


void print_csv(std::string dir, std::string scheme, Matrix analytical, Matrix solution, Vector xvalues, Vector tvalues, double time) {
	std::cout << "Exporting " << dir << std::endl;
	std::ofstream out;
	out.open(dir);
	out << "analytical" << ',' << scheme << '\n';
	int time_index = time / DELTAT;
	for (unsigned int j = 0; j < analytical.getNcols(); j++) {
		out << analytical[time_index][j] << ',' << solution[time_index][j];
		out << '\n';
	}
	out.close();
}

int main(int argc, char* argv[]) {
	if (argc != 4) {
		std::cout << "Please give <scheme N time> as argument!" << std::endl;
		return 0;
	}

	std::string scheme = argv[1];
	double n = atof(argv[2]);
	double time = atof(argv[3]);

	Matrix matrix(TSIZE + 1, XSIZE + 1);
	Matrix analytical_matrix(TSIZE + 1, XSIZE + 1);

	Vector xvalues(XSIZE + 1);
	Vector tvalues(TSIZE + 1);

	for (double i = 0; i <= XSIZE; i++) {
		xvalues[i] = i * DELTAX;
		matrix[0][i] = 0.0;
	}
	for (double t = 0; t <= TSIZE; t++) {
		matrix[t][0] = 0.0;
		matrix[t][XSIZE] = 1.0;
		tvalues[t] = DELTAT * t;
	}
	std::stringstream time_stream;
	time_stream << std::fixed << std::setprecision(1) << time;

	if (scheme == "simpleexplicit") {
		simple_excplicit_scheme(matrix);
	} else {
		std::cout << "Not a valid scheme: " << scheme << std::endl;
		return 0;
	}
	solve_analytically(analytical_matrix, n, xvalues, tvalues);
	print_csv("./matrices/" + scheme + time_stream.str() + ".csv", scheme, analytical_matrix, matrix, xvalues, tvalues, time);
}
