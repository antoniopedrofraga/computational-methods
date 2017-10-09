#ifndef ANALYTICALSOLVER_H  
#define ANALYTICALSOLVER_H

#include "../solver.h"

class AnalyticalSolver:Solver {
public:
	void computeSolution(Matrix &matrix);
};

#endif