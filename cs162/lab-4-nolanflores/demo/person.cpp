#include <iostream>
#include <string>

#include "person.hpp"

person* create_person_array(int size){
	person *array = new person[size];
	return array;
}

void init_person_array(person* array, int size) {
	for (int i = 0; i < size; i++) {
		std::cout << "Enter name for person " << (i + 1) << ": ";
		std::cin >> array[i].name;
		std::cout << "Enter age for person " << (i + 1) << ": ";
		std::cin >> array[i].age; 
		std::cout << std::endl;
	}
	return;
}

void print_person_array (person* array, int size){
	for (int i = 0; i < size; ++i)
	{
		std::cout << "person " << i+1 << ": " << std::endl;
		std::cout << "Name: " << array[i].name << std::endl;
		std::cout << "Age: " << array[i].age << std::endl;
		std::cout << std::endl;
	}
	return;
}

void delete_person_array(person* array){
	delete [] array;
}
