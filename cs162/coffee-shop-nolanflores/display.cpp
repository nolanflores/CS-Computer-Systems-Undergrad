#include <iostream>
#include "display.h"

#include "coffee.h"
#include "order.h"

/*
 * Name: print_options()
 * Description: Print options to the user
 */
void print_options() {
	std::cout << "\nWhat would you like to do?" << std::endl;
	std::cout << "	1. View shop info" << std::endl;
	std::cout << "	2. Add an item to menu" << std::endl;
	std::cout << "	3. Remove an item from menu" << std::endl;
	std::cout << "	4. Search by coffee name" << std::endl;
	std::cout << "	5. Search by price" << std::endl;
	std::cout << "	6. Place an order" << std::endl;
	std::cout << "	7. Log out" << std::endl;
}

/*
 * Name: print_selection_error
 * Description: Scolds the user for selecting a bad option
 *		number
 */
void print_selection_error() {
	std::cout << std::endl << "Error: You must choose one of the 7 options provided"
		<< std::endl << std::endl;
}

/*
 * Name: get_option
 * Description: gets a user inputed integer between 1 and 7
 * returns (int): the user's choice
 */
int get_option() {
	int option;
	bool first = true;
	do {
		if (!first) {
			print_selection_error();
		}
		first = false;
		print_options();
		std::cout << "Selection: ";
		std::cin >> option;
	} while (option < 1 || option > 7);

	return option;
}

/*
 * Name: get_name
 * Description: prompts the user for the single word name of a coffee
 * Returns (std::string): the user inputed name
*/
std::string get_name(){
	std::string name;
	std::cout << "\nEnter the name of the coffee (1 word): ";
	std::cin >> name;
	return name;
}

/*
 * Name: get_small
 * Description: prompts the user for the price of a small coffee
 * Returns (double): price of a small coffee
*/
double get_small(){
	double cost;
	std::cout << "Enter price of small size (8oz): ";
	std::cin >> cost;
	return cost;
}

/*
 * Name: get_medium
 * Description: prompts the user for the price of a medium coffee
 * Returns (double): price of a medium coffee
*/
double get_medium(){
	double cost;
	std::cout << "Enter price of medium size (12oz): ";
	std::cin >> cost;
	return cost;
}

/*
 * Name: get_large
 * Description: prompts the user for the price of a large coffee
 * Returns (double): price of a large coffee
*/
double get_large(){
	double cost;
	std::cout << "Enter price of large size (16oz): ";
	std::cin >> cost;
	return cost;
}

/*
 * Name: get_max_price
 * Description: Prompts the user for the maximum price they would be willing to spend on a coffee
 * Returns (double): price willing to pay
 */
double get_max_price(){
	double price;
	std::cout << "\nEnter your budget for one drink, and I will list out our products that cheaper or equal to your budget: ";
	std::cin >> price;
	return price;
}

/*
 * Name: execute_options
 * Description: executes the desired actions with the shop object based on the user inputed choice
 * 		1: prints the information about the shop, menu, and pending orders
 * 		2: adds a coffee to the menu from user inputed name and prices for small, medium and large cups
 * 		3: removes a coffee from the menu based off of user choice
 * 		4: prints out the info of a coffee on the menu based on the name inputed by the user
 * 		5: prints out all of the coffees with sizes that cost less than a user inputed max price
 * 		6: Prompts the user for a coffee, size, and quantity to make an order
 * Parameters
 * 		s (shop&): reference to the shop object we want to complete actions with
 * 		optiom (int): the number choice the user wants to do
*/
void execute_option(shop& s, int option) {
	if (option == 1) {
		s.print_shop_info();
	} else if (option == 2) {
		std::string name = get_name();
		double small = get_small(), medium = get_medium(), large = get_large();
		coffee c(name, small, medium, large);
		s.add_coffee_to_menu(c);
	} else if (option == 3) {
		s.get_menu().print_coffees();
		s.get_menu().remove_coffee();
	} else if (option == 4) {
		std::string name = get_name();
		s.get_menu().search_by_name(name);
	} else if (option == 5) {
		double price = get_max_price();
		s.get_menu().search_by_price(price);
	} else if (option == 6) {
		s.get_menu().print_coffees();
		s.make_order();
	}
}
