#include "explicit.h"
#include "forward_t_central_s.h"

Explicit::Explicit(Wall wall) : Method(wall) {
	double delta_t = wall.get_deltat(), delta_x = wall.get_deltax();
	q = (2 * delta_t * DIFUSIVITY) / pow(delta_x, 2);
}


void Explicit::compute_solution() {
	FTCS ftcs(wall);
	Vector current_step, previous_step, next_step;
	unsigned int t_size = wall.get_tsize(), x_size = wall.get_xsize();
	double delta_t = wall.get_deltat(), time;
	current_step = next_step = Vector(x_size + 1);
	for (unsigned int i = 1; i <= t_size; i++) {
		if (i == 1) {
			previous_step = wall.get_first_row();
			current_step = ftcs.build_iteration(Vector(0), previous_step);
		}
		next_step = build_iteration(current_step, previous_step);
		previous_step = current_step;
		current_step = next_step;
		time = delta_t * (double)i;
		wall.set_time_step(current_step, time);
	}
}