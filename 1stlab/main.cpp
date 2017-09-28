#include <iostream>
#include "matrix.h"

const double XSIZE = 100;
const double DELTAX = 80 / XSIZE;
const double DELTAT = 0.1;
const double TSIZE = 20 / DELTAT;
const double A = 1;

double sign(double value) {
	if (value < 0) {
		return -1.0;
	} else if (value == 0) {
		return 0.0;
	} else {
		return 1.0;
	}
}

void upwind_scheme(Matrix & f) {
	for (int n = 1; n < TSIZE; n++) {
		for (int i = 1; i < XSIZE; i++) {
			f[n][i] = f[n - 1][i] - A * DELTAT * (f[n - 1][i] - f[n - 1][i - 1]) / DELTAX;
		}
	}
}

void central_difference_scheme(Matrix & f) {
	for (int n = 1; n < TSIZE; n++) {
		for (int i = 1; i < XSIZE; i++) {
			f[n][i] = (f[n][i + 1] - f[n][i - 1]) / (2 * DELTAX);
		}
	}
}

void analitical_solution(Matrix & f, Vector & x, Vector & t) {
	for (int n = 0; n <= TSIZE; n++) {
		for (int i = 0; i <= XSIZE; i++) {
			f[n][i] = 0.5 * (sign(x[i] - t[n]) + 1);
		}
	}
}

void compute_errors(Matrix & a, Matrix & b, Matrix & e) {
	for (int n = 0; n <= TSIZE; n++) {
		for (int i = 0; i <= XSIZE; i++) {
			e[n][i] = a[n][i] - b[n][i];
		}
	}
}

void print_csv(const char* name, Matrix matrix) {
	std::ofstream out;
	out.open(name);
	for (unsigned int i = 0; i < matrix.getNrows(); i++) {
	  for (unsigned int j = 0; j < matrix.getNcols(); j++)
	    out << matrix[i][j] << ',';
	  out << '\n';
	}
	out.close();
}

int main() {
	Matrix explicitf(TSIZE + 1, XSIZE + 1);
	Matrix analiticalf(TSIZE + 1, XSIZE + 1);
	Matrix error_matrix(TSIZE + 1, XSIZE + 1);

	Vector xvalues(XSIZE + 1);
	Vector tvalues(TSIZE + 1);
	
	for (double i = 0; i <= XSIZE; i++) {
		xvalues[i] = -40 + (i * DELTAX);
		explicitf[0][i] = 0.5 * (sign(xvalues[i]) + 1);
	}
	for (double t = 0; t <= TSIZE; t++) {
		explicitf[t][0] = 0;
		explicitf[t][XSIZE] = 1;
		tvalues[t] = DELTAT * t;
	}

	//upwind_scheme(explicitf);
	central_difference_scheme(explicitf);
	analitical_solution(analiticalf, xvalues, tvalues);
	compute_errors(explicitf, analiticalf, error_matrix);
	
	std::cout << std::endl << "DELTAX = " << DELTAX << std::endl;
	std::cout << "DELTAT = " << DELTAT << std::endl << std::endl;
	for (double t = 1; t <= TSIZE; t++) {
		if (tvalues[t] == 5 || tvalues[t] == 10 || tvalues[t] == 20) {
			Vector vector(error_matrix[t]);
			std::cout << "1st norm at " << tvalues[t] << ": " << vector.one_norm() << std::endl;
			std::cout << "2nd norm at  " << tvalues[t] << ": " << vector.two_norm() << std::endl;
			std::cout << "uniform norm at " << tvalues[t] << ": " << vector.uniform_norm() << std::endl << std::endl;
		}
	}
	/*print_csv("./matrices/explicit.csv", explicitf);
	print_csv("./matrices/analitical.csv", analiticalf);
	print_csv("./matrices/error.csv", error_matrix);
	*/
	return 0;
}