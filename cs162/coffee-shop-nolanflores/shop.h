#ifndef SHOP_H
#define SHOP_H

#include <string>
#include <fstream>

#include "menu.h"
#include "order.h"

class shop {
private:
	menu m;

	std::string phone;
	std::string address;
	double revenue = 0;

	// Number of orders
	int num_orders = 0;

	// Base address of order array (nullptr if array is empty)
	order* orders = nullptr;
public:
	/*
	 * Name: shop (default constructor)
	 * Description: Constructs a shop with a defaultly-constructed menu,
	 *		an empty phone number and address, 0 revenue, and no orders.
	 */
	shop();

	/*
	 * Name: shop (copy constructor)
	 * Description: Constructs a shop object that is a deep copy of an existing shop
	*/
	shop(const shop& s);

	/*
	 * Name: operator= (Assignment Operator Overload)
	 * Description: Overides a shop object into a deep copy
	 */
	void operator=(const shop& s);

	/*
	 * Name: ~shop (deconstructor)
	 * Description: Frees all dynamic member variables as shop falls out of scope
	*/
	~shop();

	/*
	 * Name: add_coffee_to_menu
	 * Description: Adds a coffee to the shop's menu
	 * Parameters:
	 *		c (const coffee&): The coffee to add to the shop's menu
	 * Post conditions: Coffee added to menu
	 */
	void add_coffee_to_menu(const coffee& c);

	/*
	 * NOTE: THIS IS A REQUIRED FUNCTION. DO NOT ALTER ITS PROTOTYPE.
	 *		YOU MUST IMPLEMENT IT IN `shop.cpp`. THIS FUNCTION IS USED
	 *		BY THE BIG 3 TESTING SCRIPT.
	 * Name: add_order
	 * Description: Adds an order to the order array
	 * Parameters:
	 *		o (const order&): The order to add to the array
	 * Post conditions: Order added to array (array may need to be
	 *		reallocated, and num_orders should be incremented by 1)
	 */
	void add_order(const order& o);

	/*
	 * Name: populate_from_file
	 * Description: Parses data from a file into the shop object
	 * 		reads the shop info into the member variables
	 * Precondition:
	 * 		file is formatted with the first line being the shop phone number
	 * 		and the second line being the shop address
	 * Parameters:
	 * 		file (std::ifstream&): Reference to the input file object to read
	*/
	void populate_from_file(std::ifstream& file);

	/*
	 * Name: get_menu
	 * Description: getter for the menu member variable
	 * 		this feels like it is breaking encapsulation, but it's the best way
	 * 		I could think of doing this
	 * Returns (menu&): reference to the member menu
	*/
	menu& get_menu();

	/*
	 * Name: print_shop_info
	 * Description: prints out the shop phone and address, calls the menu's
	 * 		print function, as well as iterates through and prints the orders
	*/
	void print_shop_info() const;

	/*
	 * Name: make_order
	 * Description: prompts the user for the coffee type, size and quantity, and then
	 * 		instantiates an order object with those criteria, then calls the add_order
	 * 		function to add it to the orders. As well as adds to the revenue based on the order
	*/
	void make_order();
};

#endif
