#ifndef LU_H  //include guard
#define LU_H

#include <iostream>
#include "matrix.h"

void lu_fact(const Matrix& a, Matrix& l, Matrix& u, int n);

void lu_solve(const Matrix& l, const Matrix& u, Vector b, int n, Vector& x);

void lu_reorder(const Matrix& a, int n, Matrix &b);

#endif