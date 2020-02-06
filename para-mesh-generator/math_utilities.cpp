#include "math_utilities.h"

unsigned power_floor(unsigned x) {
	int power = 1;
	while (x >>= 1) power <<= 1;
	return power;
}

unsigned power_ceil(unsigned x) {
	if (x <= 1) return 1;
	int power = 2;
	x--;
	while (x >>= 1) power <<= 1;
	return power;
}