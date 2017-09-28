#include <iostream>
#include "matrix.h"

const double DELTAX = 0.8; /* 8 / 10 */
const double DELTAT = 1;
const double TSIZE = 20 / DELTAT + 1;
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

void explicit_solution(Matrix & f) {
	for (int n = 0; n < TSIZE - 1; n++) {
		for (int i = 1; i <= 99; i++) {
			f[n + 1][i] = f[n][i] - A * (f[n][i] - f[n][i - 1]) / DELTAX;
		}
	}
}

void analitical_solution(Matrix & f, Vector & x) {
	for (int n = 0; n < TSIZE; n++) {
		for (int i = 0; i <= 100; i++) {
			f[n][i] = 0.5 * (sign(x[i] - n) + 1);
		}
	}
}
void compute_errors(Matrix & a, Matrix & b, Matrix & e) {
	for (int n = 0; n < TSIZE; n++) {
		for (int i = 0; i <= 100; i++) {
			e[n][i] = a[n][i] - b[n][i];
		}
	}
}

int main() {
	Matrix explicitf(TSIZE, 101);
	Matrix analiticalf(TSIZE, 101);
	Matrix error_matrix(TSIZE, 101);

	Vector xvalues(101);
	
	for (double i = 0; i <= 100; i++) {
		xvalues[i] = -40 + (i * DELTAX);
		explicitf[0][i] = 0.5 * (sign(xvalues[i]) + 1);
	}
	for (double t = 0; t < TSIZE; t++) {
		explicitf[t][0] = 0;
		explicitf[t][100] = 1;
	}

	explicit_solution(explicitf);
	analitical_solution(analiticalf, xvalues);
	compute_errors(explicitf, analiticalf, error_matrix);

	for (double t = 1; t < TSIZE; t++) {
		if (t * DELTAT == 5 || t * DELTAT == 10 || t * DELTAT == 15 || t * DELTAT == 20) {
			Vector vector(error_matrix[t]);
			std::cout << "1st norm at " << t * DELTAT << ": " << vector.one_norm() << std::endl;
			std::cout << "2nd norm at  " << t * DELTAT << ": " << vector.two_norm() << std::endl;
			std::cout << "uniform norm at " << t * DELTAT << ": " << vector.uniform_norm() << std::endl << std::endl;
		}
	}
	/*
	std::cout << "1st norm: " << error_matrix.one_norm() << std::endl;
	std::cout << "2nd norm: " << error_matrix.two_norm() << std::endl;
	std::cout << "uniform norm: " << error_matrix.uniform_norm() << std::endl;
	*/
	return 0;
}