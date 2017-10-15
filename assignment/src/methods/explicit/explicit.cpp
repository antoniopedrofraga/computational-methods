#include "explicit.h"

Explicit::Explicit(Wall wall) : Method(wall) {
	unsigned int x_size = wall.get_xsize();
	this->current_iteration = this->temp_a = this->temp_b = Vector(x_size + 1);
}