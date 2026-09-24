#ifndef MENU_H
#define MENU_H

#include "coffee.h"

class menu {
private:
	// Number of coffees in menu
	int num_coffees = 0;

	// Base address of coffee array (nullptr if array is empty)
	coffee* coffees = nullptr;
public:
	/*
	 * Name: menu (default constructor)
	 * Description: Constructs a menu with an empty coffee array
	 */
	menu();

	/*
	 * Name: menu (copy constructor)
	 * Description: Constructs a deep copy of an existing menu object
	 */
	menu(const menu& m);

	/*
	 * Name: operator= (Assignment Operator Overload)
	 * Description: Overides a menu object into a deep copy
	 */
	void operator=(const menu& m);

	/*
	 * Name: ~menu (deconstructor)
	 * Description: Frees all dynamic member variables as menu falls out of scope
	*/
	~menu();

	/*
	 * Name: populate_from_file
	 * Description: Parses data from afile into the menu object
	 * 		reads existing menu into coffee array and num_coffees
	 * Precondition:
	 * 		file is formatted with the first line being the number of
	 * 		coffees and every subsequyent line holds the name and prices
	 * 		of each of the x ammounts of coffees
	 * Parameters:
	 * 		file (std::ifstream&): Reference to the input file object to read
	*/
	void populate_from_file(std::ifstream& file);

	/*
	 * Name: wrtie_to_file
	 * Description: Writes the number of coffees, the name, and the prices of all
	 * 		of the coffee objects into a text file
	 * Paramters:
	 * 		file (std::ofstream&): reference to the output file to write to
	*/
	void write_to_file(std::ofstream& file);

	/*
	 * Name: print_coffee_prices
	 * Description: Parses through the coffees array, and prints their names
	 * 		as well as the cost for all three cup sizes to the terminal
	*/
	void print_coffee_prices() const;

	/*
	 * Name: print_coffees
	 * Description: Parses through the coffees array, and prints their names only
	 * 		to the terminal
	*/
	void print_coffees() const;

	/*
	 * Name: add_coffee
	 * Description: Adds a coffee to the coffee array
	 * Parameters:
	 *		c (const coffee&): The coffee to add to the array
	 * Post conditions: Coffee added to array (array may need to be
	 *		reallocated, and num_coffees should be incremented by 1)
	 */
	void add_coffee(const coffee& c);

	/*
	 * Name: Prompts the user for an index of the coffees array, and then creates
	 * 		a new array without said index, replacing the current coffees array,
	 * 		effectively deleting the chosen index from the array
	*/
	void remove_coffee();

	/*
	 * Name: search_by_name
	 * Description: takes in a string containing the name of a supposed coffee,
	 * 		iterates through the coffee array, and prints out the cost of the 3
	 * 		cup sizes for that coffee. Prints an error message if there is no
	 * 		coffee in the array with that name
	 * Parameters:
	 * 		name (const std::string): the name of the coffee we're looking for
	*/
	void search_by_name(const std::string name) const;

	/*
	 * Name: search_by_price
	 * Description: takes in a double, iterates through the coffees array,
	 * 		and prints out all sizes of the different coffees that are
	 * 		cheaper than the inputed double cost
	 * Paramters:
	 * 		cost (const double): the maximum price of coffees to be printed
	*/
	void search_by_price(const double price) const;

	/*
	 * Name: get_coffees
	 * Description: getter for the pointer to the base address of the coffees member array
	 * 		It kinda breaks encapsulation, and I'm sure I could work around it, but it was
	 * 		the easiest way i could think of to do the coffee order option
	 * Returns (coffee*): pointer to the coffees array
	*/
	coffee* get_coffees() const;

	/*
	 * Name: get_num_coffees
	 * Description: getter for the num_coffees member variable
	 * 		also kinda breaks encapsulation, but whatever
	 * Returns (int): number of coffee objects in the coffees array
	*/
	int get_num_coffees() const;
};

#endif
