/* zphysics.cpp */

#include "zphysics.h"

void ZPhysics::add(int p_value) {
	count += p_value;
}

void ZPhysics::reset() {
	count = 0;
}

int ZPhysics::get_total() const {
	return count;
}

void ZPhysics::_bind_methods() {
	ClassDB::bind_method(D_METHOD("add", "value"), &ZPhysics::add);
	ClassDB::bind_method(D_METHOD("reset"), &ZPhysics::reset);
	ClassDB::bind_method(D_METHOD("get_total"), &ZPhysics::get_total);
}

ZPhysics::ZPhysics() {
	count = 0;
}