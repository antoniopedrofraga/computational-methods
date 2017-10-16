#include "method.h"

Method::Method() {}

Method::~Method() {}

Method::Method(Wall wall) {
	this->wall = wall;
}

std::string Method::get_name() {
	return name;
}

Matrix Method::get_grid() {
	return (*wall.get_grid());
}
