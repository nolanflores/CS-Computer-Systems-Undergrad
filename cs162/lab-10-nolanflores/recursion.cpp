#include "recursion.hpp"

int no_zero_strings(int n) {
	int num_strings = 0;
	if (n == 1) {
		num_strings = 2;
	} else if (n == 2) {
		num_strings = 3;
	} else {
		num_strings += no_zero_strings(n - 1) + no_zero_strings(n - 2);
	}
	return num_strings;
}
