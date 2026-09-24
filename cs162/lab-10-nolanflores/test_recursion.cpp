#include <iostream>

#include "recursion.hpp"

void print_test_case(int n, int correct) {
	int prediction = no_zero_strings(n);
	std::cout << "Correct output for no_zero_strings(" <<
		n << "):         " << correct << std::endl;
	std::cout << "Your function's output for no_zero_strings(" <<
		n << "): " << prediction;
	
	if (correct != prediction) {
		std::cout << " (ERROR! INCORRECT ANSWER)";
	}
	std::cout << std::endl << std::endl;
}

int main() {
	print_test_case(1, 2);
	print_test_case(2, 3);
	print_test_case(3, 5);
	print_test_case(4, 8);
	print_test_case(10, 144);
}
