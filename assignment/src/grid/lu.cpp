#include "lu.h"

void lu_fact(const Matrix& a, Matrix& l, Matrix& u, int n) {
	Matrix temp = a;
	double mult;
	int i,j,k;
	
	// LU (Doolittle's) decomposition without pivoting
	for (k = 0; k < n - 1; k++) {
		for (i = k + 1; i < n; i++) {
			if (fabs(temp[k][k]) < 1.e-07) 
			{ 
				printf("pivot is zero\n"); 
				exit(1);
			}
			mult = temp[i][k]/temp[k][k];
			temp[i][k] = mult;                      // entries of L are saved in temp
			for (j = k + 1; j < n; j++) { 
				temp[i][j] -= mult*temp[k][j];      // entries of U are saved in temp
				if (fabs(temp[i][i]) < 1.e-07)
				{ 
					printf("pivot is zero\n"); 
					exit(1);
				}
			}
		}
	}

	// create l and u from temp
	for (i=0; i<n; i++) l[i][i] = 1.0;
	for (i=1; i<n; i++) 
	  for (j=0; j<i; j++) l[i][j] = temp[i][j];

	for (i=0; i<n; i++)
		for (j=i; j<n; j++) u[i][j] = temp[i][j];

	return;
}

void lu_solve(const Matrix& l, const Matrix& u, Vector b, int n, Vector& x)
{
	Vector temp(b);
	int i,j; 
	
	// forward substitution for L y = b.
	for (i = 1; i < n; i++) 
		for (j = 0; j < i; j++) 
			temp[i] -= l[i][j]*temp[j];
	
  
	// back substitution for U x = y.  
	for (i = n - 1; i >= 0; i--) {
		for (j = i + 1; j < n; j++) temp[i] -= u[i][j]*temp[j];
		temp[i] /= u[i][i];
	}

	// copy solution into x
	for (i=0; i<n; i++) x[i] = temp[i];

	return;
}

void lu_reorder(const Matrix& a, int n, Matrix &p) 
{
// Note: pivoting information is stored in temperary vector pvt

	int i,j,k;
	int pvtk,pvti;
	double aet, tmp, mult;

	Vector pvt = Vector(n);
	Vector scale = Vector(n);
	Matrix temp = a;

	for (k = 0; k < n; k++) pvt[k] = k;

	for (k = 0; k < n; k++) {
		scale[k] = 0;
		for (j = 0; j < n; j++) 
			if (fabs(scale[k]) < fabs(temp[k][j])) scale[k] = fabs(temp[k][j]);
	} 

	for (k = 0; k < n - 1; k++) {            // main elimination loop

	// find the pivot in column k in rows pvt[k], pvt[k+1], ..., pvt[n-1]
		int pc = k; 
		aet = fabs(temp[pvt[k]][k]/scale[k]);
		for (i = k + 1; i < n; i++) {
			tmp = fabs(temp[pvt[i]][k]/scale[pvt[i]]); 
			if (tmp > aet) {
				aet = tmp; 
				pc = i;
			}
		}
		if (fabs(aet) < 1.e-07) 
		{ 
			printf("pivot is zero\n"); 
			exit(1); 
		}
		if (pc != k) {                      // swap pvt[k] and pvt[pc]
			int ii = pvt[k];
			pvt[k] = pvt[pc];
			pvt[pc] = ii;
		}

		// now eliminate the column entries logically below mx[pvt[k]][k]
		pvtk = pvt[k];                           // pivot row
		for (i = k + 1; i < n; i++) {
			pvti = pvt[i];
			if (temp[pvti][k] != 0) {
				mult = temp[pvti][k]/temp[pvtk][k]; 
				temp[pvti][k] = mult;
				for (j = k + 1; j < n; j++) temp[pvti][j] -= mult*temp[pvtk][j];
			}
		}
	}
	for (i=0; i<n; i++) p[i][pvt[i]]=1.0;

} 
