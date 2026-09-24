#ifndef COFFEE_H
#define COFFEE_H

#include <string>

class coffee {
private:
	std::string name;
	double small_cost = 0.0;
	double medium_cost = 0.0;
	double large_cost = 0.0;

public:
	/*
	 * Name: coffee (default constructor)
	 * Description: Constructs a coffee object with an empty name
	 *		and all costs of 0
	 */
	coffee();

	/*
	 * Name: coffee (non-default constructor)
	 * Description: constructs a coffee with a name and costs from parameters
	 * Parameters
	 *      name (std::string): the name of the coffee type
	 *      small (double): the price for a small cup of this coffee
	 *      medium (double): the price for a medium cup of this coffee
	 *      large (double): the price for a large cup of this coffee
	*/
	coffee(std::string name, double small, double medium, double large);

	/*
	 * Name: set_name
	 * Description: setter for the name member variable
	 * Parameters
	 *      name (std::string): the new name for the coffee
	*/
	void set_name(std::string name);

	/*
	 * Name: set_small_cost
	 * Description: setter for the small_cost member variable
	 * Parameters
	 *      cost (double): the new cost for a small coffee
	*/
	void set_small_cost(double cost);

	/*
	 * Name: set_medium_cost
	 * Description: setter for the medium_cost member variable
	 * Parameters
	 *      cost (double): the new cost for a medium coffee
	*/
	void set_medium_cost(double cost);

	/*
	 * Name: set_large_cost
	 * Description: setter for the large_cost member variable
	 * Parameters
	 *      cost (double): the new cost for a large coffee
	*/
	void set_large_cost(double cost);

	/*
 	 * Name: get_name
 	 * Description: getter for the name member variable
 	 * Returns (std::string): the name of the coffee
	*/
	std::string get_name() const;

	/*
 	 * Name: get_small_cost
 	 * Description: getter for the small_cost member variable
 	 * Returns (double): the cost of a small cup
	*/
	double get_small_cost() const;

	/*
	 * Name: get_medium_cost
	 * Description: getter for the medium_cost member variable
	 * Returns (double): the cost of a medium cup
	*/
	double get_medium_cost() const;

	/*
	 * Name: get_large_cost
	 * Description: getter for the large_cost member variable
	 * Returns (double): the cost of a large cup
	*/
	double get_large_cost() const;
};

#endif
