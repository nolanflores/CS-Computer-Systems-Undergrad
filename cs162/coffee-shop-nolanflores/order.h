#ifndef ORDER_H
#define ORDER_H

#include <string>

class order {
private:
	int order_number = 0;
	std::string coffee_name;
	char coffee_size = 0;
	int quantity = 0;
public:
	/* 
	 * Name: order (default constructor)
	 * Description: Constructs an order with order_number 0,
	 *		empty coffee name, null (0) coffee size, and 0
	 *		quantity.
	 */
	order();

	/*
	 * Name: order (non-default constructor):
	 * Description: Constructs an order object with all member variables instantiated
	 * 		by the constructor parameters
	*/
	order(int num, std::string name, char size, int quantity);

	/*
	 * Name: get_order_number
	 * Description: getter for the order_number member variable
	 * Returns (int): the order number
	*/
	int get_order_number() const;

	/*
	 * Name: get_coffee_name
	 * Description: getter for the coffee_name member variable
	 * 		coffee_name is the name/type of coffee from the menu
	 * Returns (std::string): the name of the coffee in the order
	*/
	std::string get_coffee_name() const;

	/*
	 * Name: get_coffee_size
	 * Description: getter for the coffee_size member variable
	 * 		coffee_size is the cup size the user wants to buy
	 * Returns (char): 's', 'm', or 'l' to represent small, medium, or large
	*/
	char get_coffee_size() const;

	/*
	 * Name: get_quantity
	 * Description: getter for the quantity member variable
	 * 		quantity is the number of coffee cups the user wants to buy
	 * Returns (std::string): the name of the coffee in the order
	*/
	int get_quantity() const;
};

#endif
