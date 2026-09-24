/*
 * Author: Nolan Flores
 * Description: Test script for ways_to_top() implementation
 */

#include <iostream>

#include "stairs.hpp"

/*********************************************************************
 ** Function: main()
 ** Description: outputs ways to the top of different sized staicases
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ********************************************************************/
int main() {
	std::cout << std::endl << "3-Step Staircase: " << ways_to_top(3) <<
		" ways" << std::endl; // Should prints "4 ways"

	std::cout << "4-Step Staircase: " << ways_to_top(4) << " ways" <<
		std::endl; // Should print "7 ways"

	std::cout << "5-Step Staircase: " << ways_to_top(5) << " ways" <<
		std::endl; // Should print "13 ways"

	std::cout << "6-Step Staircase: " << ways_to_top(6) << " ways" <<
		std::endl; // Should print "24 ways"

	std::cout << "7-Step Staircase: " << ways_to_top(7) << " ways" <<
		std::endl << std::endl; // Should print "44 ways"
}
