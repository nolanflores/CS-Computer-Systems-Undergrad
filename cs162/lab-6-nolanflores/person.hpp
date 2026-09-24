#ifndef PERSON_HPP
#define PERSON_HPP

#include "dog.hpp"

class person {
	// Pointer to dynamic array of dogs. You may want to give this a default
	// value, or maybe not.
	dog* pets;

	// Integer that records how many pets / dogs this person has
	int num_pets;
public:
	
	person();

	person(int num_pets);

	~person();
};

#endif
