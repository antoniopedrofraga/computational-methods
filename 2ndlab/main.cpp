#include <string>
#include <iomanip>
#include <sstream>
#include <lapacke.h>
#include "lu.h"

double DELTAX = 0.02;
double DELTAT = 0.01;
double XSIZE = 1 / DELTAX;
double TSIZE = 10 / DELTAT;
const double D = 0.01;
const double PI = std::atan(1)*4;
double R = (DELTAT * D) / pow(DELTAX, 2);

//extern "C" void DGESV(int *n, int *nrhs, Matrix *a, int *lda, int *ipiv, double *b, int *ldb, int *info);

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

void thomas(Matrix & f) {
	for (int n = 0; n < TSIZE; n++) {
		Vector p(XSIZE), y(XSIZE - 1);
		for (int i = 0; i < XSIZE; i++) {
			if (i == 0) {
				y[i] = -R / (1 + 2 * R);
				p[i] = (f[n][i + 1] + R * f[n][i]) / (1 + 2 * R);
			} else if (i == XSIZE - 1) {
				p[i] = (f[n][i + 1] + R * f[n][i] + R * p[i - 1]) / ((1 + 2 * R) + R * y[i - 1]);
			} else {
				y[i] = -R / ((1 + 2 * R) + R * y[i - 1]);
				p[i] = (f[n][i] + R * p[i - 1]) / ((1 + 2 * R) + R * y[i - 1]);
			}
		}
		f[n + 1][XSIZE - 1] = p[XSIZE - 1];
		for (int i = XSIZE - 1; i >= 0; i--) {
			f[n + 1][i] = p[i] - y[i] * f[n + 1][i + 1];
		}
	}
}

void lu_b_vector(Vector matrix_vector, Vector & b_vector) {
	unsigned int size = b_vector.getSize();
	for (int i = 0; i < size; i++) {
		if (i == 0) {
			b_vector[i] = matrix_vector[i + 1] + R *  matrix_vector[i];
		} else if(i == size - 1) {
			b_vector[i] = matrix_vector[i + 2] + R *  matrix_vector[i + 1];
		} else {
			b_vector[i] = matrix_vector[i + 1];
		}
	}
}

void lu_b_vector_lapack(Vector matrix_vector, double ** b_vector) {
	unsigned int size = XSIZE - 1;
	for (int i = 0; i < size; i++) {
		if (i == 0) {
			(*b_vector)[i] = matrix_vector[i + 1] + R *  matrix_vector[i];
		} else if(i == size - 1) {
			(*b_vector)[i] = matrix_vector[i + 2] + R *  matrix_vector[i + 1];
		} else {
			(*b_vector)[i] = matrix_vector[i + 1];
		}
	}
}


void lu_create_a(Matrix & a, int size) {
	for (int i = 0; i < size; i++) {
		a[i][i] = (1 + 2 * R);
		if (i == 0) {
			a[i][i + 1] = -R;
		} else if (i == size - 1) {
			a[i][i - 1] = -R;
		} else {
			a[i][i + 1] = -R;
			a[i][i - 1] = -R;
		}
	}
}

void lu_partial_pivoting(Matrix & f) {
	int size = XSIZE - 1;
	Matrix a(size, size), l(size, size), u(size, size);
	lu_create_a(a, size);
	lu_fact(a, l, u, size);
	for (int n = 0; n < TSIZE; n++) {
		Vector b(size), c(size);
		lu_b_vector(f[n], c);
		lu_solve(l, u, c, size, b);
		f.set_row_from_lu_b(size, n + 1, b);
	}
}

void lu_lapack(Matrix & f) {
	lapack_int size = XSIZE - 1;
	double a[size][size];

	for (int i = 0; i < size; i++) {
		a[i][i] = (1 + 2 * R);
		if (i == 0) {
			a[i][i + 1] = -R;
		} else if (i == size - 1) {
			a[i][i - 1] = -R;
		} else {
			a[i][i + 1] = -R;
			a[i][i - 1] = -R;
		}
	}

	lapack_int pivd[size];
	for (int n = 0; n < TSIZE; n++) {
		double *b = (double*) malloc(size * sizeof(double));
		lapack_int info;
		lu_b_vector_lapack(f[n], &b);
		info = LAPACKE_dgesv(LAPACK_ROW_MAJOR , size, 1 , *a , 1, pivd , b , 1);
		if (info == 0) {
			std::cout << "lapack factorization went well!" << std::endl;
		} else if(info < 0) {
			std::cout << "lapack factorization had a problem with the " << fabs(info) << " element. That element has an illegal value!" << std::endl;
		} else {
			std::cout <<  "U(" << info << ", " << info << ") is exactly zero.  The factorization has been completed, but the factor U is exactly singular, so the solution could not be computed." << std::endl;
		}
	}
}
void simple_excplicit(Matrix & f) {
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
	for (unsigned int j = 0; j <= XSIZE; j++) {
		out << analytical[time_index][j] << ',' << solution[time_index][j];
		out << '\n';
	}
	out.close();
}

int main(int argc, char* argv[]) {
	if (argc != 6) {
		std::cout << "Please give <scheme N time r deltax> as argument!" << std::endl;
		return 0;
	}
	std::string scheme = argv[1];
	double n = atof(argv[2]);
	double time = atof(argv[3]);
	R = atof(argv[4]);
	DELTAX = atof(argv[5]);
	DELTAT = R * pow(DELTAX, 2) / D;
	XSIZE = (int)(1 / DELTAX);
	TSIZE = (int)(10 / DELTAT);
	std::cout << XSIZE << " x " << TSIZE << std::endl;

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

	if (scheme == "simpleexplicit") {
		simple_excplicit(matrix);
	} else if (scheme == "thomas") {
		thomas(matrix);
	} else if (scheme == "lupartialpivoting") {
		lu_partial_pivoting(matrix);
	} else if (scheme == "lulapack") {
		lu_lapack(matrix);
	} else {
		std::cout << "Not a valid scheme: " << scheme << std::endl;
		return 0;
	}

	std::stringstream time_stream;
	time_stream << "t=";
	time_stream << std::fixed << std::setprecision(2) << time;
	time_stream << "r=";
	time_stream  << std::fixed << std::setprecision(2) << R;
	
	solve_analytically(analytical_matrix, n, xvalues, tvalues);
	print_csv("./matrices/" + scheme + time_stream.str() + ".csv", scheme, analytical_matrix, matrix, xvalues, tvalues, time);
}
