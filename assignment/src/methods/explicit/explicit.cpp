#include "explicit.h"
#include "forward_t_central_s.h"

Explicit::Explicit(Problem problem) : Method(problem) {
	double delta_t = problem.get_deltat(), delta_x = problem.get_deltax();
	q = (2 * delta_t * DIFUSIVITY) / pow(delta_x, 2);
}


void Explicit::compute_solution() {
	FTCS ftcs(problem);
	Vector current_step, previous_step, next_step;
	unsigned int t_size = problem.get_tsize(), x_size = problem.get_xsize();
	double delta_t = problem.get_deltat(), time;
	current_step = next_step = Vector(x_size + 1);
	for (unsigned int i = 1; i <= t_size; i++) {
		if (i == 1) {
			previous_step = problem.get_first_row();
			current_step = ftcs.build_iteration(Vector(0), previous_step);
		}
		next_step = build_iteration(current_step, previous_step);
		previous_step = current_step;
		current_step = next_step;
		time = delta_t * (double)i;
		problem.set_time_step(current_step, time);
	}
}