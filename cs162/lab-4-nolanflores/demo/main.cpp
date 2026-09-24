#include <iostream>

#include "person.hpp"

int main()
{
	// Prompt the user for the size of the array
	int size;
	std::cout << "Enter number of people: ";
	std::cin >> size;

	// Allocate array's memory
	person *people = create_person_array(size);

	// Initialize / populate the array
	init_person_array(people, size);

	// Print the array
	print_person_array(people, size);

	// Delete the array
	delete_person_array(people);
	people = nullptr; // Assigning to null is good practice

	return 0;
}
