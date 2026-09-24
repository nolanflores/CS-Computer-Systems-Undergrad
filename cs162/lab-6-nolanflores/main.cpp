#include "person.hpp"

int main() {
	// Person with no pets
	person samantha;

	// Person with 5 pets
	person mary(5);

	// Once you've implemented a destructor for the person class, samantha's
	// and mary's destructors should be called the moment they fall out of
	// scope here. This should free mary's dynamic array of dogs.
}
