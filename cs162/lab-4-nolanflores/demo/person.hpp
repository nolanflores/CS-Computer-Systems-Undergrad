#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>

// Define the struct type person
struct person {
	std::string name; 
	int age;
};

/*
 * Function name: create_person_array
 * Description: allocate memory for an array of person objects, with size
 *		provided
 * Parameters:
 *		size (int): Size of the array
 * Returns: Base address of dynamically allocated array of person objects
 * Post-conditions: Dynamic array of person objects allocated (base address
 *		returned; must be deleted later to avoid a memory leak)
 */
person* create_person_array(int size);

/*
 * Function name: init_person_array
 * Description: Initialize the elements of the given array of person objects
 *		according to user inputs
 * Parameters:
 *		array (person*): Pointer to the base address of the person array to
 *			initialize. Must point to a valid (allocated) array.
 *		size (int): Size of the array
 * Post-conditions: The given person array is populated according to user
 *		inputs
 */
void init_person_array(person* array, int size);

/*
 * Function name: print_person_array
 * Description: Print the given array of person objects
 * Parameters:
 *		array (person*): Pointer to the base address of the person array to
 *			print. Must point to a valid (allocated) array.
 *		size (int): Size of the array
 * Post-conditions: The contents of the array of person objects is printed
 * 		to the terminal
 */
void print_person_array (person* array, int size);

/*
 * Function name: delete_person_array
 * Description: Free the memory allocated for the array of person objects
 * Parameters:
 *		array (person*): Pointer to the base address of the person array to
 *			free. Must point to a valid (allocated) array.
 * Post-conditions: The memory allocated for the array of person objects
 *		is freed.
 */
void delete_person_array(person* array);

#endif
