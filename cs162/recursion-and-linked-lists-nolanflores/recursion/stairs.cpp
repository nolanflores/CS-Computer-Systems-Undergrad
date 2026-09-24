#include "stairs.hpp"

int ways_to_top(int n) {
	int ways = 0;
	if(n == 0)
		return 1;
	if(n >= 1)
		ways += ways_to_top(n-1);
	if(n >= 2)
		ways += ways_to_top(n-2);
	if(n >= 3)
		ways += ways_to_top(n-3);
	return ways;
}
