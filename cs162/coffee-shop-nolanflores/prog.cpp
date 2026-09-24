/*
 * Author: Nolan Flores
 * Oregon State University
 * College of Engineering
 * Description: Simulates a coffee shop, giving the user options to see a menu,
 * 		see info about the shop, modify the menu, and make orders
*/

#include <iostream>
#include "display.h"

#include <fstream>

int main() {
	std::cout << "Welcome to the Coffee++ Cafe!" << std::endl;

	//initialize values into a shop from shop_info.txt
	shop s;
	std::ifstream info_file, menu_file;
	info_file.open("shop_info.txt");
	if(!info_file.is_open()){
		std::cout << "Error: info file not found!" << std::endl;
		return -1;
	}
	s.populate_from_file(info_file);
	info_file.close();

	//populate all of the cofffee data in menu from menu.txt
	menu_file.open("menu.txt");
	if(!menu_file.is_open()){
		std::cout << "Error: menu file not found!" << std::endl;
		return -1;
	}
	s.get_menu().populate_from_file(menu_file);
	menu_file.close();

	//loop through the user choices until quit
	int option;
	do {
		option = get_option();
		if (option >= 1 && option <= 6) {
			execute_option(s, option);
		}
	} while (option != 7);

	std::ofstream menu_out;
	menu_out.open("menu.txt");
	s.get_menu().write_to_file(menu_out);
	menu_out.close();

	return 0;
}
